#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<cmath>

#define ROW 923
// #define COL 1127
#define COL 1131

using namespace std;
using namespace chrono;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
    bool outline = false; //建物の輪郭判定
};

// read file and strage points as an array
// void input_raw(vector<vector<Point>>& geometry, ifstream& file_in)
// {
//     Point trash;
//     for (int j = 0; j < 897; ++j)
//     {
//         file_in >> trash.x >> trash.y >> trash.z;
//     }
//     for (int i = 0; i < ROW; ++i)
//     {
//         file_in >> trash.x >> trash.y >> trash.z;
//         file_in >> trash.x >> trash.y >> trash.z;
//         for (int j = 0; j < COL; ++j)
//         {
//             file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
//         }
//     }
// }

void input_raw(vector<vector<Point>>& geometry, ifstream& file_in)
{
    Point *trash;
    trash = new Point;
    for (int j = 0; j < 897; ++j)
    {
        file_in >> trash->x >> trash->y >> trash->z;
    }
    for (int i = 0; i < 308; ++i)
    {
        for (int j = 0; j < 377; ++j) //376
        {
            // file_in >> trash->x >> trash->y >> trash->z;
            // file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        for (int j = 377; j < 754; ++j) //376, 752
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        for (int j = 754; j < COL; ++j) //752
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        // file_in >> trash->x >> trash->y >> trash->z;
        // file_in >> trash->x >> trash->y >> trash->z;
    }
    for (int i = 308; i < 616; ++i)
    {
        for (int j = 0; j < 377; ++j)
        {
            // file_in >> trash->x >> trash->y >> trash->z;
            // file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        for (int j = 377; j < 754; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        for (int j = 754; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        // file_in >> trash->x >> trash->y >> trash->z;
        // file_in >> trash->x >> trash->y >> trash->z;
    }
    for (int i = 616; i < ROW; ++i)
    {
        for (int j = 0; j < 377; ++j)
        {
            // file_in >> trash->x >> trash->y >> trash->z;
            // file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        for (int j = 377; j < 754; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        for (int j = 754; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
        // file_in >> trash->x >> trash->y >> trash->z;
        // file_in >> trash->x >> trash->y >> trash->z;
    }
    delete trash;
}

// write points to file
void output_complemented(vector<vector<Point>>& geometry, ofstream& file_out)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << endl;
        }
    }
}

// read file and strage points as an array
void input_complemented(vector<vector<Point>>& geometry, ifstream& file_in)
{   
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z ;
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

// read file and strage points as an array
void input_distinguished(vector<vector<Point>>& geometry, ifstream& file_in)
{   
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z >> geometry[i][j].isBuilding >> geometry[i][j].outline;
        }
    }
}

// write points to file
void output_removed(vector<vector<Point>>& removed, ofstream& file_out)
{
    int row = int(removed.size());
    int col = int(removed[0].size());
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            file_out << removed[i][j].x << ' ' << removed[i][j].y << ' ' << removed[i][j].z << ' ' << removed[i][j].isBuilding << endl;
        }
    }
}

double mean_of_neighbourhood(double neighbourhood[], int len)
{
    double sum_value = 0;
    int crash_num = 0;
    //平均値
    for (int i = 0; i < len; ++i)
    {
        if(neighbourhood[i] == -9999.99){
            ++crash_num;
            continue;
        }
        sum_value += neighbourhood[i];
    }
    return sum_value / (len - crash_num);
}

void complement(vector<vector<Point>>& geometry)
{
    for (int i = 1; i < ROW - 1; ++i)
    {
        for (int j = 1; j < COL - 1; ++j)
        {
            if(geometry[i][j].z == -9999.99){
                // 8近傍
                double neighbourhood[8] = {geometry[i - 1][j - 1].z,
                                           geometry[i - 1][j].z,
                                           geometry[i - 1][j + 1].z,
                                           geometry[i][j - 1].z,
                                           geometry[i][j + 1].z,
                                           geometry[i + 1][j - 1].z,
                                           geometry[i + 1][j].z,
                                           geometry[i + 1][j + 1].z};
                geometry[i][j].z = mean_of_neighbourhood(neighbourhood, 8);
            }
        }
    }
    for (int i = 1; i < COL - 1; ++i)
    {
        if(geometry[0][i].z == -9999.99){
            double neighbourhood[5] = {geometry[1][i].z,
                                       geometry[1][i + 1].z,
                                       geometry[0][i + 1].z,
                                       geometry[0][i - 1].z,
                                       geometry[1][i - 1].z};
            geometry[0][i].z = mean_of_neighbourhood(neighbourhood, 5);
        }
    }
    for (int i = 1; i < COL - 1; ++i)
    {
        if(geometry[ROW - 1][i].z == -9999.99){
            double neighbourhood[5] = {geometry[ROW - 2][i].z,
                                       geometry[ROW - 2][i + 1].z,
                                       geometry[ROW - 2][i - 1].z,
                                       geometry[ROW - 1][i - 1].z,
                                       geometry[ROW - 1][i + 1].z};
            geometry[ROW - 1][i].z = mean_of_neighbourhood(neighbourhood, 5);
        }
    }
    for (int i = 1; i < ROW - 1; ++i)
    {
        if(geometry[i][0].z == -9999.99){
            double neighbourhood[5] = {geometry[i][1].z,
                                       geometry[i + 1][1].z,
                                       geometry[i - 1][1].z,
                                       geometry[i + 1][0].z,
                                       geometry[i - 1][0].z};
            geometry[i][0].z = mean_of_neighbourhood(neighbourhood, 5);
        }
    }
    for (int i = 1; i < ROW - 1; ++i)
    {
        if(geometry[i][COL - 1].z == -9999.99){
            double neighbourhood[5] = {geometry[i][COL - 2].z,
                                       geometry[i + 1][COL - 2].z,
                                       geometry[i - 1][COL - 2].z,
                                       geometry[i + 1][COL - 1].z,
                                       geometry[i - 1][COL - 1].z};
            geometry[i][COL - 1].z = mean_of_neighbourhood(neighbourhood, 5);
        }
    }
    if(geometry[0][0].z == -9999.99){
        double neighbourhood[3] = {geometry[0][1].z,
                                   geometry[1][0].z,
                                   geometry[1][1].z};
        geometry[0][0].z =mean_of_neighbourhood(neighbourhood, 3);
    }
    if(geometry[0][COL - 1].z == -9999.99){
        double neighbourhood[3] = {geometry[0][COL - 2].z,
                                   geometry[1][COL - 2].z,
                                   geometry[1][COL - 1].z};
        geometry[0][COL - 1].z =mean_of_neighbourhood(neighbourhood, 3);
    }
    if(geometry[ROW - 1][0].z == -9999.99){
        double neighbourhood[3] = {geometry[ROW - 1][1].z,
                                   geometry[ROW - 2][0].z,
                                   geometry[ROW - 2][1].z};
        geometry[ROW - 1][0].z =mean_of_neighbourhood(neighbourhood, 3);
    }
    if(geometry[ROW - 1][COL - 1].z == -9999.99){
        double neighbourhood[3] = {geometry[ROW - 1][COL - 2].z,
                                   geometry[ROW - 2][COL - 2].z,
                                   geometry[ROW - 2][COL - 1].z};
        geometry[ROW - 1][COL - 1].z =mean_of_neighbourhood(neighbourhood, 3);
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

void smoothing(vector<vector<Point>>& removed)
{
    int row = int(removed.size());
    int col = int(removed[0].size());
    for(int i = 1; i < row - 1; ++i)
    {
        for(int j = 1; j < col - 1; ++j)
        {
            int num_building = 0;
            double min_height = removed[i][j-1].z;
            if(removed[i][j].isBuilding == true){
                if(removed[i][j-1].isBuilding == true) ++num_building;
                if(removed[i-1][j-1].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i-1][j-1].z) min_height = removed[i-1][j-1].z;
                }
                if(removed[i-1][j].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i-1][j].z) min_height = removed[i-1][j].z;
                }
                if(removed[i-1][j+1].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i-1][j+1].z) min_height = removed[i-1][j+1].z;
                }
                if(removed[i][j+1].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i][j+1].z) min_height = removed[i][j+1].z;
                }
                if(removed[i+1][j+1].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i+1][j+1].z) min_height = removed[i+1][j+1].z;
                }
                if(removed[i+1][j].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i+1][j].z) min_height = removed[i+1][j].z;
                }
                if(removed[i+1][j-1].isBuilding == true){
                    ++num_building;
                    if(min_height > removed[i+1][j-1].z) min_height = removed[i+1][j-1].z;
                }
                if(num_building < 4){
                    removed[i][j].isBuilding = false;
                    removed[i][j].z = min_height;
                }
            }           
        }
    }
}

// from 9 points to 1 point
void remove(vector<vector<Point>>& geometry, vector<vector<Point>>& removed)
{
    int row = 0;
    int col;
    for (int i = 0; i < ROW - 2; i += 3) // ROW - k + 1; i += k
    {
        col = 0;
        for (int j = 0; j < COL - 2; j += 3) // COL - k + 1; i += k
        {
            int num_building = geometry[i][j].isBuilding
                             + geometry[i][j + 1].isBuilding 
                             + geometry[i][j + 2].isBuilding 
                             + geometry[i + 1][j].isBuilding 
                             + geometry[i + 1][j + 1].isBuilding
                             + geometry[i + 1][j + 2].isBuilding
                             + geometry[i + 2][j].isBuilding
                             + geometry[i + 2][j + 1].isBuilding
                             + geometry[i + 2][j + 2].isBuilding;

            removed[row][col].x = geometry[i + 1][j + 1].x;
            removed[row][col].y = geometry[i + 1][j + 1].y;
            if (num_building >= 5){
                removed[row][col].z = (geometry[i][j].z * geometry[i][j].isBuilding
                             + geometry[i][j + 1].z * geometry[i][j + 1].isBuilding
                             + geometry[i][j + 2].z * geometry[i][j + 2].isBuilding
                             + geometry[i + 1][j].z * geometry[i + 1][j].isBuilding
                             + geometry[i + 1][j + 1].z * geometry[i + 1][j + 1].isBuilding
                             + geometry[i + 1][j + 2].z * geometry[i + 1][j + 2].isBuilding
                             + geometry[i + 2][j].z * geometry[i + 2][j].isBuilding
                             + geometry[i + 2][j + 1].z * geometry[i + 2][j + 1].isBuilding
                             + geometry[i + 2][j + 2].z * geometry[i + 2][j + 2].isBuilding)/num_building; // 建物点の平均値
                removed[row][col].isBuilding = true;
            }else{
                removed[row][col].z = (geometry[i][j].z * !geometry[i][j].isBuilding
                             + geometry[i][j + 1].z * !geometry[i][j + 1].isBuilding
                             + geometry[i][j + 2].z * !geometry[i][j + 2].isBuilding
                             + geometry[i + 1][j].z * !geometry[i + 1][j].isBuilding
                             + geometry[i + 1][j + 1].z * !geometry[i + 1][j + 1].isBuilding
                             + geometry[i + 1][j + 2].z * !geometry[i + 1][j + 2].isBuilding
                             + geometry[i + 2][j].z * !geometry[i + 2][j].isBuilding
                             + geometry[i + 2][j + 1].z * !geometry[i + 2][j + 1].isBuilding
                             + geometry[i + 2][j + 2].z * !geometry[i + 2][j + 2].isBuilding)/(double)(9 - num_building); // 地面点の平均値
                removed[row][col].isBuilding = false;
            }
            col++;
        }
        row++;
    }
}