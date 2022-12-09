//distinguish ground points from building points
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<chrono>
#include<memory>
#include<algorithm>

#define ROW 923
#define COL 1131

using namespace std;
using namespace chrono;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
    bool outline = false; //建物の輪郭判定
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
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << ' ' << geometry[i][j].isBuilding << ' ' <<  geometry[i][j].outline << endl;
        }
    }
}

int sgjudge(std::vector<std::vector<Point>> geometry,int row,int col,int end[310][380],int rowsize,int colsize,int gmax){
    for(int i=-1; i<2; i++){
                for(int j=-1; j<2; j++){
                    if(row+i>=0&&col+j>=0&&(row+i<rowsize&&col+j<colsize)){
                       if(i==0&&j==0){
                    }else if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=0.5&&end[row+i][col+j]==0&&geometry[row+i][col+j].z<=gmax){
                    return 0;//まだ探索できる点があった
                    }else{
                    }
                     }
            }
    }
     return 1;
}

void gjudge(std::vector<std::vector<Point>>& geometry,int& row,int& col,int& n,std::vector<int>& pastrow, std::vector<int>& pastcol,bool& t,int rowsize,int colsize,int gmax,int end[310][380],std::vector<int>& saverow,std::vector<int>& savecol)
{
    int i,j;
    for(i=-1; i<2; i++){
            //隣接点走査
            for(j=-1; j<2; j++){
                if((row+i>=0&&col+j>=0)&&(row+i<rowsize&&col+j<colsize)){
            if(i==0&&j==0){
            }else if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=0.5&&geometry[row+i][col+j].isBuilding==true&&geometry[row+i][col+j].z<=gmax){
                //地面判定できる点があった
                 pastrow.push_back(row);
                 pastcol.push_back(col);//1つ前の行列の添え字
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
                geometry[row][col].outline=true;//建物の輪郭であることの更新
            }
                }
            }
        }
}

void judge(std::vector<std::vector<Point>>& jgeometry,int startrow,int startcol,int rowsize, int colsize,int gmax,int end[310][380])
{
    
    std::vector<int> pastrow;//1つ前の点の行の添え字
    std::vector<int> pastcol;//1つ前の点の列の添え字
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
            int k=savecol.size();
            if(k<600){
                /*k=1030000/n/114.5*/
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
            pastrow.pop_back();
            pastcol.pop_back();
            n--;
            //1つ前の点に戻って走査を再開する
        }
    }
}

void output_complemented(vector<vector<Point>>& geometry, ofstream& file_out)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << ' ' << geometry[i][j].isBuilding << endl;
        }
    }
}

int main()
{

     system_clock::time_point start, endtime;
      start = system_clock::now();
    // string input_path = "250_records_complemented.txt";
    string input_path = "53394640_dsm_1m_complemented.txt";

    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }

    // string output_path = "53394640_dsm_1m_distinguished.txt";
    string output_path = "53394640_dsm_1m_distinguished.txt";

    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input_complemented(geometry, file_in);

    
    

    
 //ここでエリアの行数と列数を求める
    int row,col;
    row=geometry.size();//行数の取得
    col=geometry.at(0).size();//列数の取得
    int i,j,k,l,n=10,sr=0,limit,av_sr=0,av_sm=0;//nは分割数(9なら3)
    int nrow=row/n;//行数を均等に分割
    int ncol=col/n;//列数を均等に分割
    int arow=row%n;//あまり
    int acol=col%n;//あまり
    int p_n_row=nrow,p_n_col=ncol;//現在いるエリアの列数,行数
    int srow=0,scol=0;//どこまで行列を使用したか(geometryからjgeometryへの代入操作時に必要)
    int end[310][380]={0};//探索済みの印
    double sumz=0,summ=0;
    vector<vector<Point>> jgeometry(nrow+arow,vector<Point>(ncol+acol));
    vector<double> sort_geometry((nrow+arow)*(ncol+acol),0);
    for(k=0; k<n; k++){
        if(k==n-1) p_n_row+=arow;
        for(l=0; l<n; l++){
             if(l==n-1) p_n_col+=acol;
             for(i=0; i<p_n_row; i++){
                    for(j=0; j<p_n_col; j++){
                        jgeometry[i][j]=geometry[i+srow][j+scol];
                        sort_geometry[sr]=geometry[i+srow][j+scol].z;
                        if(geometry[i+srow][j+scol].z<=15&&geometry[i+srow][j+scol].z>5){
                        summ+=geometry[i+srow][j+scol].z;
                        av_sm++;
                        }
                        if(geometry[i+srow][j+scol].z<=25&&geometry[i+srow][j+scol].z>15){
                        sumz+=geometry[i+srow][j+scol].z;
                        av_sr++;
                        }
                        sr++;
                    }
    }

    //上限値の決定
    if(av_sr!=0){
        limit=sumz/av_sr+3;
    }
    else if(av_sm!=0){
        limit=summ/av_sm+3;
    }else{
        limit=0;
    }
        for(i=0; i<p_n_row; i++){
            for(j=0; j<p_n_col; j++){
                end[i][j]=0;
            }
        }
       
        for(i=0; i<p_n_row; i++){
            for(j=0; j<p_n_col; j++){
                if(jgeometry[i][j].z<=limit&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                    judge(jgeometry,i,j,p_n_row,p_n_col,limit,end);
                }
            }
        }
        for(i=0; i<p_n_row; i++){
            for(j=0; j<p_n_col; j++){
                geometry[i+srow][j+scol]=jgeometry[i][j];
            }
        }
            scol+=p_n_col;
            sr=0;
            sumz=0;
            summ=0;
            av_sr=0;
            av_sm=0;
            if(l==n-1) p_n_col-=acol;
            }
            if(k==n-1) p_n_row-=arow;
            scol=0;
            srow+=p_n_row;
        }
        output_distinguished(geometry, file_out);
         endtime = system_clock::now();
         std::cout << duration_cast<nanoseconds>(endtime - start).count() << " nanosec" << endl;
}