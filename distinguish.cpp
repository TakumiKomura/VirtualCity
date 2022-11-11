//distinguish ground points from building points
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<chrono>
#include<memory>

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
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z  << ' ' << geometry[i][j].isBuilding <<  endl;
        }
    }
}

int sgjudge(std::vector<std::vector<Point>> geometry,int row,int col,int end[400][400],int rowsize,int colsize,int gmax){
    for(int i=-1; i<2; i++){
                for(int j=-1; j<2; j++){
                    if(row+i>=0&&col+j>=0&&(row+i<rowsize&&col+j<colsize)){
                       if(i==0&&j==0){
                    }else if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=1.5&&end[row+i][col+j]==0&&geometry[row+i][col+j].z<=gmax){
                    return 0;//まだ探索できる点があった
                    }else{
                    }
                     }
            }
    }
     return 1;
}

void gjudge(std::vector<std::vector<Point>>& geometry,int& row,int& col,int& n,int pastrow[], int pastcol[],bool& t,int rowsize,int colsize,int gmax,int end[400][400],std::vector<int>& saverow,std::vector<int>& savecol)
{
    int i,j;
    for(i=-1; i<2; i++){
            //隣接点走査
            for(j=-1; j<2; j++){
                if((row+i>=0&&col+j>=0)&&(row+i<rowsize&&col+j<colsize)){
            if(i==0&&j==0){
            }else if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=1.5&&geometry[row+i][col+j].isBuilding==true&&geometry[row+i][col+j].z<=gmax){
                //地面判定できる点があった
                pastrow[n]=row;
                pastcol[n]=col;//1つ前の行列の添え字
                 saverow.push_back(row);
                 savecol.push_back(col);
                n++;
                /*std::cout << geometry[row+i][col+j].z << "\n";*/
                row=row+i;//次の点の行列の添え字
                col=col+j;
                geometry[row][col].isBuilding=false;//地面であることの更新
                t=false;
                return;
            }else{
                end[row+i][col+j]=1;
            }
                }
            }
        }
}

void judge(std::vector<std::vector<Point>>& jgeometry,int startrow,int startcol,int rowsize, int colsize,int gmax,int end[400][400])
{
    
    int pastrow[120000]={0};//1つ前の点の行の添え字
    int pastcol[120000]={0};//1つ前の点の列の添え字
    std::vector<int> saverow;
    std::vector<int> savecol;
    int row=startrow;//行
    int col=startcol;//列
    int n=0,completed=0;//繰り返し文に必要なフラグ
    saverow.push_back(row);
    savecol.push_back(col);
    jgeometry[row][col].isBuilding=false;
    while(completed==0){
         if(row==startrow&&col==startcol){//探索地点がスタート地点まで戻った時の処理
            completed=sgjudge(jgeometry,row,col,end,rowsize,colsize,gmax);
         }
         if(completed==1){
            if(saverow.size()<500){
                int k=savecol.size();
                for(int i=0; i<k; i++){
                    jgeometry[saverow[i]][savecol[i]].isBuilding=true;
                }
            }
            return;
         }
         bool t=true;
        gjudge(jgeometry,row,col,n,pastrow,pastcol,t,rowsize,colsize,gmax,end,saverow,savecol);
        if((t==true&&n-1>=0)){
            //隣接点を走査したが地面判定された点はなかった時
            end[row][col]=1;//隣接点が地面でないことをすべて確認した印
            row=pastrow[n-1];
            col=pastcol[n-1];
            /*std::cout << pastrow[n-1] << " " << pastcol[n-1] << " " << n << "\n";*/
            n--;
            //1つ前の点に戻って走査を再開する
        }
    }
}

/*void output_complemented(vector<vector<Point>>& geometry, ofstream& file_out)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << ' ' << geometry[i][j].isBuilding << endl;
        }
    }
}*/

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

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;

    vector<vector<Point>> jgeometry(ROW,vector<Point>(COL));
    int i,j,a,b;
    int end[400][400]={0};//探索済みの印
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            jgeometry[i][j]=geometry[i][j];
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=25&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,308,377,25,end);
            }
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            geometry[i][j]=jgeometry[i][j];
        }
    }

    for(i=0; i<308; i++){
        for(j=377; j<754; j++){
            jgeometry[i][j-377]=geometry[i][j];
        }
    }
    end[400][400]={0};
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=17&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,308,377,17,end);
            }
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            geometry[i][j+377]=jgeometry[i][j];
        }
    }
 

    for(i=0; i<308; i++){
        for(j=754; j<COL; j++){
            jgeometry[i][j-754]=geometry[i][j];
        }
    }
     end[400][400]={0};
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=23&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,308,377,23,end);
            }
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            geometry[i][j+754]=jgeometry[i][j];
        }
    }
   

    for(i=308; i<615; i++){
        for(j=0; j<377; j++){
            jgeometry[i-308][j]=geometry[i][j];
        }
    }
    a=0,b=0;
     end[400][400]={0};
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=23&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,307,377,23,end);
            }
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            geometry[i+308][j]=jgeometry[i][j];
        }
    }
      
    for(i=308; i<616; i++){
        for(j=377; j<754; j++){
            jgeometry[i-308][j-377]=geometry[i][j];
        }
    }
    end[400][400]={0};
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=23&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,308,377,23,end);
            }
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            geometry[i+308][j+377]=jgeometry[i][j];
        }
    }
 
    for(i=308; i<616; i++){
        for(j=754; j<COL; j++){
            jgeometry[i-308][j-754]=geometry[i][j];
        }
    }
     end[400][400]={0};
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=25&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,308,377,25,end);
            }
        }
    }
    for(i=0; i<308; i++){
        for(j=0; j<377; j++){
            geometry[i+308][j+754]=jgeometry[i][j];
        }
    }
    

   for(i=616; i<ROW; i++){
        for(j=0; j<377; j++){
            jgeometry[i-616][j]=geometry[i][j];
            }
        }
    end[400][400]={0};
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=25&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,307,377,25,end);
            }
        }
    }
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            geometry[i+616][j]=jgeometry[i][j];
        }
    }

    for(i=616; i<ROW; i++){
        for(j=377; j<755; j++){
            jgeometry[i-616][j-377]=geometry[i][j];
        }
    }
     end[400][400]={0};
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=9&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,307,377,9,end);
            }
        }
    }
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            geometry[i+616][j+377]=jgeometry[i][j];
        }
    }
    

    for(i=616; i<ROW; i++){
        for(j=755; j<COL; j++){
            jgeometry[i-616][j-755]=geometry[i][j];
        }
    }
    end[400][400]={0};
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            if(jgeometry[i][j].z<=25&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                judge(jgeometry,i,j,307,377,25,end);
            }
        }
    }
    for(i=0; i<307; i++){
        for(j=0; j<377; j++){
            geometry[i+616][j+755]=jgeometry[i][j];
        }
    }
    // write points to file
    output_distinguished(geometry, file_out);
    return 0;
}