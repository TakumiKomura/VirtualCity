//distinguish ground points from building points
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<chrono>

#define ROW 923
#define COL 1131

using namespace std;
using namespace chrono;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
    int area;
};

// read file and strage points as an array
void input_complemented(vector<vector<Point>>& geometry, ifstream& file_in)
{   
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z >> geometry[i][j].area;
        }
    }
}

// write points to file
void output_distinguished(vector<vector<Point>>& geometry, ofstream& file_out)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << endl;
        }
    }
}

void judge(std::vector<std::vector<Point>> geometry,int startrow,int startcol)
{
    
    int pastrow[10000];//1つ前の点の行の添え字
    int pastcol[10000];//1つ前の点の列の添え字
    int end[10000][10000];//探索済みの印
    int row=startrow;//行
    int col=startcol;//列
    int n=0,completed=0;//繰り返し文に必要なフラグ
    while(completed==0){
         if(row==startrow&&col==startcol){//探索地点がスタート地点まで戻った時の処理
            for(int i=-1; i<2; i++){
                for(int j=-1; j<2; j++){
                    if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=0.5&&end[row+i][col+j]==0){
                    break;//まだ探索できる点があった
                    }
                    if(i==1&&j==1){
                        completed=1;//隣接点はすべて探索していた
                    }
                }
            }
         }
         if(completed==1) break;
         int i,j;
        for(i=-1; i<2; i++){
            //隣接点走査
            for(j=-1; j<2; j++){
            if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=0.5&&geometry[row+i][col+j].isBuilding!=false){
                //地面判定できる点があった
                pastrow[n]=row;
                pastcol[n]=col;//1つ前の行列の添え字
                n++;
                row=row+i;//次の点の行列の添え字
                col=col+j;
                geometry[row][col].isBuilding=0;//地面であることの更新
                break;
            }
            }
        }
        if(i==2&&j==2){
            //隣接点を走査したが地面判定された点はなかった時
            end[row][col]=1;//隣接点が地面でないことをすべて確認した印
            int r=pastrow[n-1];
            int c=pastcol[n-1];
            pastrow[n-1]=0;//使用済みの添え字を0にする
            pastcol[n-1]=0;
            n--;
            judge(geometry,r,c);//1つ前の点に戻って走査を再開する
            //pastの1番後ろの要素を削除する
        }
    }
}

int main()
{
    // string input_path = "250_records_complemented.txt";
    string input_path = "53394640_dsm_1m_complemented.txt";

    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }

    // string output_path = "250_records_distinguished.txt";
    string output_path = "53394640_dsm_1m_distinguished.txt";

    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input_complemented(geometry, file_in);
    output_distinguished(geometry, file_out);

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;

 vector<vector<Point>> jgeometry;
    int min=9999,slow,scol;
    for(int i=0; i<308; i++){
        for(int j=0; j<377; j++){
            jgeometry[i][j]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
     for(int i=0; i<308; i++){
        for(int j=377; j<754; j++){
            jgeometry[i][j-377]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=0; i<308; i++){
        for(int j=754; j<COL; j++){
            jgeometry[i][j-754]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=308; i<616; i++){
        for(int j=0; j<377; j++){
            jgeometry[i-308][j]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=308; i<616; i++){
        for(int j=377; j<754; j++){
            jgeometry[i-308][j-377]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=308; i<616; i++){
        for(int j=754; j<COL; j++){
            jgeometry[i-308][j-754]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=616; i<ROW; i++){
        for(int j=0; j<377; j++){
            jgeometry[i-616][j]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=616; i<ROW; i++){
        for(int j=377; j<754; j++){
            jgeometry[i][j-377]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
    for(int i=616; i<ROW; i++){
        for(int j=754; j<COL; j++){
            jgeometry[i][j-754]=geometry[i][j];
            if(jgeometry[i][j].z<=min){
                min=jgeometry[i][j].z;
                slow=i;
                scol=j;
            }
        }
    }
    judge(jgeometry,slow,scol);
    jgeometry.clear();
}