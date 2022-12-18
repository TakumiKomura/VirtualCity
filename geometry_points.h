#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<cmath>

#define ROW 923
#define COL 1131

using namespace std;
using namespace chrono;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
};

// read file and strage points as an array
void input_raw(vector<vector<Point>>& geometry, ifstream& file_in)
{
    Point trash;
    for (int j = 0; j < 897; ++j)
    {
        file_in >> trash.x >> trash.y >> trash.z;
    }
    for (int i = 0; i < ROW; ++i)
    {
        // 左端の2列を捨てる
        // file_in >> trash.x >> trash.y >> trash.z;
        // file_in >> trash.x >> trash.y >> trash.z;
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
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

int sgjudge(vector<vector<Point>>& geometry, int row, int col, int end[310][380], int rowsize, int colsize, int gmax){
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if((row + i >= 0 && col + j >= 0) && (row + i < rowsize && col + j < colsize)){
                if(i == 0 && j == 0){
                }else if(std::fabs(geometry[row + i][col + j].z - geometry[row][col].z) <= 0.5 && end[row + i][col + j] == 0 && geometry[row + i][col + j].z <= gmax){
                    return 0;//まだ探索できる点があった
                }else{
                }
            }
        }
    }
    
    return 1;
}

void gjudge(vector<vector<Point>>& geometry, int row, int col, int& n, vector<int>& pastrow, vector<int>& pastcol, bool& t, int rowsize, int colsize, int gmax, int end[310][380], vector<int>& saverow, vector<int>& savecol)
{
    int i, j;
    for(i =- 1; i < 2; i++){
        //隣接点走査
        for(j = -1; j < 2; j++){
            if((row + i >= 0 && col + j >= 0) && (row + i < rowsize && col + j < colsize)){
                if(i == 0 && j == 0){
                }else if(fabs(geometry[row + i][col + j].z - geometry[row][col].z) <= 0.5 && geometry[row + i][col + j].isBuilding == true && geometry[row + i][col + j].z <= gmax){
                    //地面判定できる点があった
                    pastrow.push_back(row);
                    pastcol.push_back(col);//1つ前の行列の添え字
                    saverow.push_back(row);
                    savecol.push_back(col);
                    n++;
                    row += i;//次の点の行列の添え字
                    col += j;
                    geometry[row][col].isBuilding = false;//地面であることの更新
                    t = false;
                    return;
                }else{
                    end[row + i][col + j] = 1;
                }
            }
        }
    }
}

void judge(vector<vector<Point>>& jgeometry, int startrow, int startcol, int rowsize, int colsize, int gmax, int end[310][380])
{ 
    vector<int> pastrow;//1つ前の点の行の添え字
    vector<int> pastcol;//1つ前の点の列の添え字
    vector<int> saverow;
    vector<int> savecol;
    int row = startrow;//行
    int col = startcol;//列
    int n = 0, completed = 0;//繰り返し文に必要なフラグ
    saverow.push_back(row);
    savecol.push_back(col);
    jgeometry[row][col].isBuilding = false;
    while(completed == 0){
        if(row == startrow && col == startcol){//探索地点がスタート地点まで戻った時の処理
            completed = sgjudge(jgeometry, row, col, end, rowsize, colsize, gmax);
        }
        if(completed == 1){
            int k = savecol.size();
            if(k < 600){
                for(int i = 0; i < k; i++){
                    jgeometry[saverow[i]][savecol[i]].isBuilding = true;
                }
            }
            return;
        }
        bool t = true;
        gjudge(jgeometry, row, col, n, pastrow, pastcol, t, rowsize, colsize, gmax, end, saverow, savecol);
        if((t == true && n - 1 >= 0)){
            //隣接点を走査したが地面判定された点はなかった時
            end[row][col] = 1;//隣接点が地面でないことをすべて確認した印
            row = pastrow[n - 1];
            col = pastcol[n - 1];
            pastrow.pop_back();
            pastcol.pop_back();
            n--;
            //1つ前の点に戻って走査を再開する
        }
    }
}

void distinguish(vector<vector<Point>>& geometry){
    //ここでエリアの行数と列数を求める
    int row, col;
    row = geometry.size();//行数の取得
    col = geometry[0].size();//列数の取得
    int i, j, k, l, n = 10, limit, av_sr = 0, av_sm = 0;//nは分割数(9なら3)
    int nrow = row / n;//行数を均等に分割
    int ncol = col / n;//列数を均等に分割
    int arow = row % n;//あまり
    int acol = col % n;//あまり
    int p_n_row = nrow, p_n_col = ncol;//現在いるエリアの列数,行数
    int srow = 0, scol = 0;//どこまで行列を使用したか(geometryからjgeometryへの代入操作時に必要)
    int end[310][380] = {0};//探索済みの印
    double sumz = 0, summ = 0;
    vector<vector<Point>> jgeometry(nrow + arow, vector<Point>(ncol + acol));
    for(k = 0; k < n; k++){
        if(k == n - 1) p_n_row += arow;
        for(l = 0; l < n; l++){
            if(l == n - 1) p_n_col += acol;
            for(i = 0; i < p_n_row; i++){
                for(j = 0; j < p_n_col; j++){
                    jgeometry[i][j] = geometry[i + srow][j + scol];
                    if(geometry[i + srow][j + scol].z <= 15 && geometry[i + srow][j + scol].z > 5){
                        summ += geometry[i + srow][j + scol].z;
                        av_sm++;
                    }
                    if(geometry[i + srow][j + scol].z <= 25 && geometry[i + srow][j + scol].z > 15){
                        sumz += geometry[i + srow][j + scol].z;
                        av_sr++;
                    }
                }
            }

            //上限値の決定
            if(av_sr != 0){
                limit = sumz / av_sr + 3;
            }
            else if(av_sm != 0){
                limit = summ / av_sm + 3;
            }else{
                limit = 0;
            }
            for(i = 0; i < p_n_row; i++){
                for(j = 0; j < p_n_col; j++){
                    end[i][j] = 0;
                }
            }
       
            for(i = 0; i < p_n_row; i++){
                for(j = 0; j < p_n_col; j++){
                    if(jgeometry[i][j].z <= limit && jgeometry[i][j].isBuilding == 1 && end[i][j] == 0){
                        judge(jgeometry,i,j,p_n_row,p_n_col,limit,end);
                    }
                }
            }
            for(i = 0; i < p_n_row; i++){
                for(j = 0; j < p_n_col; j++){
                    geometry[i + srow][j + scol] = jgeometry[i][j];
                }
            }
            scol += p_n_col;
            sumz = 0;
            summ = 0;
            av_sr = 0;
            av_sm = 0;
            if(l == n - 1) p_n_col -= acol;
        }
        if(k == n - 1) p_n_row -= arow;
        scol = 0;
        srow += p_n_row;
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
                             + geometry[i + 2][j + 2].z * geometry[i + 2][j + 2].isBuilding) / num_building; // 建物点の平均値
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