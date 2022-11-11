#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<cmath>
#include<algorithm>

#define ROW 923
#define COL 1127

using namespace std;
using namespace chrono;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
    int area;
};

// read file and strage points as an vector array
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
        for (int j = 0; j < 376; ++j)
        {
            file_in >> trash->x >> trash->y >> trash->z;
            file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 0;
        }
        for (int j = 376; j < 752; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 1;
        }
        for (int j = 752; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 2;
        }
        file_in >> trash->x >> trash->y >> trash->z;
        file_in >> trash->x >> trash->y >> trash->z;
    }
    for (int i = 308; i < 616; ++i)
    {
        for (int j = 0; j < 376; ++j)
        {
            file_in >> trash->x >> trash->y >> trash->z;
            file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 3;
        }
        for (int j = 376; j < 752; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 4;
        }
        for (int j = 752; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 5;
        }
        file_in >> trash->x >> trash->y >> trash->z;
        file_in >> trash->x >> trash->y >> trash->z;
    }
    for (int i = 616; i < ROW; ++i)
    {
        for (int j = 0; j < 376; ++j)
        {
            file_in >> trash->x >> trash->y >> trash->z;
            file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 6;
        }
        for (int j = 376; j < 752; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 7;
        }
        for (int j = 752; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 8;
        }
        file_in >> trash->x >> trash->y >> trash->z;
        file_in >> trash->x >> trash->y >> trash->z;
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
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << ' ' << geometry[i][j].area << endl;
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

// read file and strage points as an array
void input_distinguished(vector<vector<Point>>& geometry, ifstream& file_in)
{   
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
    }
}

// write points to file
void output_removed(vector<Point>& removed, ofstream& file_out)
{
    for (int i = 0; i < int(removed.size()); ++i)
    {
        file_out << removed[i].x << ' ' << removed[i].y << ' ' << removed[i].z << ' ' << removed[i].isBuilding << endl;
    }
}

double calc(double neighbourhood[], int len)
{
    double complement_value = 0;
    int crash_num = 0;
    //平均値
    for (int i = 0; i < len; ++i)
    {
        if(neighbourhood[i] == -9999.99){
            ++crash_num;
            continue;
        }
        complement_value += neighbourhood[i];
    }
    return complement_value / (len - crash_num);

    // 平均値に最も近い値
    // for (int i = 0; i < len; ++i)
    // {
    //     if(neighbourhood[i] == -9999.99){
    //         ++crash_num;
    //     }
    //     else{complement_value += neighbourhood[i];}
    // }

    // complement_value /= (len - crash_num);
    // double min = fabs(complement_value - neighbourhood[0]);
    // int min_id = 0;

    // for (int i = 1; i < len; ++i)
    // {
    //     if(min > fabs(complement_value - neighbourhood[i])){
    //         min = fabs(complement_value - neighbourhood[i]);
    //         min_id = i;
    //     }
    // }
    // return neighbourhood[min_id];

    //中央値
    // sort(neighbourhood, neighbourhood + len);
    // for (int i = 0; i < len; ++i)
    // {
    //     if(neighbourhood[i] == -9999.99){
    //         ++crash_num;
    //     }
    // }
    
    // if((len - crash_num) % 2){
    //     return neighbourhood[(len - crash_num) / 2 + crash_num];
    // }
    // else{
    //    return (neighbourhood[(len - crash_num) / 2 + crash_num] + neighbourhood[(len - crash_num) / 2 + crash_num - 1]) / 2.0;
    // }

    //最小値
    // int min = neighbourhood[0]; //配列の先頭は欠損値が入らないように送られているので問題ない
    // int min_id = 0;
    // for (int i = 1; i < len; ++i)
    // {
    //     if(neighbourhood[i] == -9999.99){
    //         continue;
    //     }
    //     if(min > neighbourhood[i]){
    //         min = neighbourhood[i];
    //         min_id = i;
    //     }
    // }
    // return neighbourhood[min_id];
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
                geometry[i][j].z = calc(neighbourhood, 8);
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
            geometry[0][i].z = calc(neighbourhood, 5);
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
            geometry[ROW - 1][i].z = calc(neighbourhood, 5);
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
            geometry[i][0].z = calc(neighbourhood, 5);
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
            geometry[i][COL - 1].z = calc(neighbourhood, 5);
        }
    }
    if(geometry[0][0].z == -9999.99){
        double neighbourhood[3] = {geometry[0][1].z,
                                   geometry[1][0].z,
                                   geometry[1][1].z};
        geometry[0][0].z =calc(neighbourhood, 3);
    }
    if(geometry[0][COL - 1].z == -9999.99){
        double neighbourhood[3] = {geometry[0][COL - 2].z,
                                   geometry[1][COL - 2].z,
                                   geometry[1][COL - 1].z};
        geometry[0][COL - 1].z =calc(neighbourhood, 3);
    }
    if(geometry[ROW - 1][0].z == -9999.99){
        double neighbourhood[3] = {geometry[ROW - 1][1].z,
                                   geometry[ROW - 2][0].z,
                                   geometry[ROW - 2][1].z};
        geometry[ROW - 1][0].z =calc(neighbourhood, 3);
    }
    if(geometry[ROW - 1][COL - 1].z == -9999.99){
        double neighbourhood[3] = {geometry[ROW - 1][COL - 2].z,
                                   geometry[ROW - 2][COL - 2].z,
                                   geometry[ROW - 2][COL - 1].z};
        geometry[ROW - 1][COL - 1].z =calc(neighbourhood, 3);
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

double _mean(double val1, double val2, double val3, double val4)
{
    return (val1 + val2 + val3 + val4) / 2;
}

double mean(double val1, double val2, double val3, double val4)
{
    return (val1 + val2 + val3 + val4) / 4;
}

double median(double val1, double val2, double val3, double val4)
{
    double big1, big2, big3, small1, small2, small3;

    if(val1 > val2){
        big1 = val1;
        small1 = val2;
    }else{
        big1 = val2;
        small1 = val1;
    }

    if(val3 > val4){
        big2 = val3;
        small2 = val4;
    }else{
        big2 = val4;
        small2 = val3;
    }

    if(big1 > big2)
        small3 = big2;
    else
        small3 = big1;
    
    if(small1 > small2)
        big3 = small1;
    else
        big3 = small2;

    return (big3 + small3) / 2;
}

double closest_to_mean(double val1, double val2, double val3, double val4)
{
    double val[4] = {val1, val2, val3, val4};
    double mean = (val1 + val2 + val3 + val4) / 4;
    double min = fabs(val[0] - mean);
    int min_idx = 0;
    double tmp;
    for (int i = 1; i < 4; i++){
        if(tmp = fabs(val[i] - mean) < min){
            min = tmp;
            min_idx = i;
        }
    }
    return val[min_idx];
}

void remove(vector<vector<Point>>& geometry, vector<Point>& removed)
{
    int count = -1;
    for (int i = 0; i < ROW; i += 2)
    {
        for (int j = 0; j < COL; j += 2)
        {
            count++;
            int num_building = geometry[i][j].isBuilding
                             + geometry[i][j + 1].isBuilding 
                             + geometry[i + 1][j].isBuilding 
                             + geometry[i + 1][j + 1].isBuilding;
            if (num_building == 2){
                removed[count].x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
                removed[count].y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
                removed[count].z = _mean(geometry[i][j].z * geometry[i][j].isBuilding,
                                        geometry[i][j + 1].z * geometry[i][j + 1].isBuilding, 
                                        geometry[i + 1][j].z * geometry[i + 1][j].isBuilding,
                                        geometry[i + 1][j + 1].z * geometry[i + 1][j + 1].isBuilding);
                removed[count].isBuilding = true;

                count++;
                removed[count].x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
                removed[count].y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
                removed[count].z = _mean(geometry[i][j].z * !geometry[i][j].isBuilding,
                                        geometry[i][j + 1].z * !geometry[i][j + 1].isBuilding, 
                                        geometry[i + 1][j].z * !geometry[i + 1][j].isBuilding,
                                        geometry[i + 1][j + 1].z * !geometry[i + 1][j + 1].isBuilding);
                removed[count].isBuilding = false;
            }else{
                removed[count].x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
                removed[count].y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
                removed[count].z = mean(geometry[i][j].z, geometry[i][j + 1].z, 
                                        geometry[i + 1][j].z, geometry[i + 1][j + 1].z);
                if ((num_building == 0) || (num_building == 1)){
                    removed[count].isBuilding = false;
                }else{
                    removed[count].isBuilding = true;
                }
            }
        }
    }
    removed.resize(count);
}