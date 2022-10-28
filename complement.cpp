// complement lack points
#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<cmath>
#include<algorithm>

// #define ROW 5 
// #define COL 50

#define ROW 923
#define COL 1131 // -4

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

// void input_raw(vector<vector<Point>>& geometry, ifstream& file_in)
// {
//     for (int i = 0; i < ROW; ++i)
//     {
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
        for (int j = 0; j < 377; ++j)
        {
            // file_in >> trash->x >> trash->y >> trash->z;
            // file_in >> trash->x >> trash->y >> trash->z;
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 0;
        }
        for (int j = 377; j < 754; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 1;
        }
        for (int j = 754; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 2;
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
            geometry[i][j].area = 3;
        }
        for (int j = 377; j < 754; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 4;
        }
        for (int j = 754; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 5;
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
            geometry[i][j].area = 6;
        }
        for (int j = 377; j < 754; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 7;
        }
        for (int j = 754; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
            geometry[i][j].area = 8;
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
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << ' ' << geometry[i][j].area << endl;
        }
    }
}

double calc(double neighbourhood[], int len)
{
    double complement_value = 0;
    int crash_num = 0;
    // 平均値
    // for (int i = 0; i < len; ++i)
    // {
    //     if(neighbourhood[i] == -9999.99){
    //         ++crash_num;
    //         continue;
    //     }
    //     complement_value += neighbourhood[i];
    // }
    // return complement_value / (len - crash_num);

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

// void complement(vector<vector<Point>>& geometry)
// {
//     for (int i = 1; i < ROW - 1; ++i)
//     {
//         for (int j = 1; j < COL - 1; ++j)
//         {
//             if(geometry[i][j].z == -9999.99){
//                 // 8近傍
//                 double neighbourhood[8] = {geometry[i - 1][j - 1].z,
//                                            geometry[i - 1][j].z,
//                                            geometry[i - 1][j + 1].z,
//                                            geometry[i][j - 1].z,
//                                            geometry[i][j + 1].z,
//                                            geometry[i + 1][j - 1].z,
//                                            geometry[i + 1][j].z,
//                                            geometry[i + 1][j + 1].z};
//                 geometry[i][j].z = calc(neighbourhood, 8);
//             }
//         }
//     }
//     for (int i = 1; i < COL - 1; ++i)
//     {
//         if(geometry[0][i].z == -9999.99){
//             double neighbourhood[5] = {geometry[1][i].z,
//                                        geometry[1][i + 1].z,
//                                        geometry[0][i + 1].z,
//                                        geometry[0][i - 1].z,
//                                        geometry[1][i - 1].z};
//             geometry[0][i].z = calc(neighbourhood, 5);
//         }
//     }
//     for (int i = 1; i < COL - 1; ++i)
//     {
//         if(geometry[ROW - 1][i].z == -9999.99){
//             double neighbourhood[5] = {geometry[ROW - 2][i].z,
//                                        geometry[ROW - 2][i + 1].z,
//                                        geometry[ROW - 2][i - 1].z,
//                                        geometry[ROW - 1][i - 1].z,
//                                        geometry[ROW - 1][i + 1].z};
//             geometry[ROW - 1][i].z = calc(neighbourhood, 5);
//         }
//     }
//     for (int i = 1; i < ROW - 1; ++i)
//     {
//         if(geometry[i][0].z == -9999.99){
//             double neighbourhood[5] = {geometry[i][1].z,
//                                        geometry[i + 1][1].z,
//                                        geometry[i - 1][1].z,
//                                        geometry[i + 1][0].z,
//                                        geometry[i - 1][0].z};
//             geometry[i][0].z = calc(neighbourhood, 5);
//         }
//     }
//     for (int i = 1; i < ROW - 1; ++i)
//     {
//         if(geometry[i][COL - 1].z == -9999.99){
//             double neighbourhood[5] = {geometry[i][COL - 2].z,
//                                        geometry[i + 1][COL - 2].z,
//                                        geometry[i - 1][COL - 2].z,
//                                        geometry[i + 1][COL - 1].z,
//                                        geometry[i - 1][COL - 1].z};
//             geometry[i][COL - 1].z = calc(neighbourhood, 5);
//         }
//     }
//     if(geometry[0][0].z == -9999.99){
//         double neighbourhood[3] = {geometry[0][1].z,
//                                    geometry[1][0].z,
//                                    geometry[1][1].z};
//         geometry[0][0].z =calc(neighbourhood, 3);
//     }
//     if(geometry[0][COL - 1].z == -9999.99){
//         double neighbourhood[3] = {geometry[0][COL - 2].z,
//                                    geometry[1][COL - 2].z,
//                                    geometry[1][COL - 1].z};
//         geometry[0][COL - 1].z =calc(neighbourhood, 3);
//     }
//     if(geometry[ROW - 1][0].z == -9999.99){
//         double neighbourhood[3] = {geometry[ROW - 1][1].z,
//                                    geometry[ROW - 2][0].z,
//                                    geometry[ROW - 2][1].z};
//         geometry[ROW - 1][0].z =calc(neighbourhood, 3);
//     }
//     if(geometry[ROW - 1][COL - 1].z == -9999.99){
//         double neighbourhood[3] = {geometry[ROW - 1][COL - 2].z,
//                                    geometry[ROW - 2][COL - 2].z,
//                                    geometry[ROW - 2][COL - 1].z};
//         geometry[ROW - 1][COL - 1].z =calc(neighbourhood, 3);
//     }
// }

int main()
{
    // string input_path = "250_records.txt";
    string input_path = "53394640_dsm_1m.dat";

    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }

    // string output_path = "250_records_complemented.txt";
    string output_path = "53394640_dsm_1m_complemented.txt";

    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input_raw(geometry, file_in);
    output_complemented(geometry, file_out);

    //どこがずれていたか調べる用
    // for(int i = 0; i < ROW; ++i){
    //     cout << geometry[i][0].x << " " << geometry[i][COL - 1].x << endl;
    //     if(i > 400 && i < 420){
    //         cout << endl << i  << endl;
    //         for(int j = 0; j < 30; ++j){
    //             cout << geometry[i][j].x << " ";
    //         }
    //     }
    // }

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // complement(geometry);
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;

    // //欠損点がどこか調べる用
    // for (int i = 0; i < ROW; ++i)
    // {
    //     for (int j = 0; j < COL; ++j)
    //     {
    //         if(geometry[i][j].z == -9999.99){
    //             cout << "(" << i << ", " << j << "): " << geometry[i][j].z << endl;
    //         }
    //     }
    // }
    // cout << "clear" <<endl;

    


    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;
}