// compliment lack points
#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>

// #define ROW 5 
// #define COL 50

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

// void input1(vector<vector<Point>>& geometry, ifstream& file_in)
// {
//     for (int i = 0; i < ROW; ++i)
//     {
//         for (int j = 0; j < COL; ++j)
//         {
//             file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
//         }
//     }
// }

void input1(vector<vector<Point>>& geometry, ifstream& file_in)
{
    Point *trash;
    trash = new Point[897];
    for (int j = 0; j < 897; ++j)
    {
        file_in >> trash[j].x >> trash[j].y >> trash[j].z;
    }
    delete[] trash;
    
    for (int i = 0; i < 308; ++i)
    {
        for (int j = 0; j < 377; ++j)
        {
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
    }
    for (int i = 308; i < 616; ++i)
    {
        for (int j = 0; j < 377; ++j)
        {
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
    }
    for (int i = 616; i < ROW; ++i)
    {
        for (int j = 0; j < 377; ++j)
        {
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
    }
}

// write points to file
void output1(vector<vector<Point>>& geometry, ofstream& file_out)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << ' ' << geometry[i][j].area << endl;
        }
    }
}

// double calc(double neighbourhood[])
// {
//     neighbourhood.
// }

// void compliment(vector<vector<Point>>& geometry)
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
//                 geometry[i][j].z = calc(neighbourhood);
//             }
//         }
//     }
//     for (int i = 1; i < COL - 1; ++i)
//     {
//         if(geometry[0][i].z == -9999.99){

//         }
//     }
//     for (int i = 1; i < COL - 1; ++i)
//     {
//         if(geometry[ROW - 1][i].z == -9999.99){
            
//         }
//     }
//     for (int i = 1; i < ROW - 1; ++i)
//     {
//         if(geometry[i][0].z == -9999.99){
            
//         }
//     }
//     for (int i = 1; i < ROW - 1; ++i)
//     {
//         if(geometry[i][COL - 1].z == -9999.99){
            
//         }
//     }
//     if(geometry[0][0].z == -9999.99){

//     }
//     if(geometry[0][COL - 1].z == -9999.99){

//     }
//     if(geometry[ROW - 1][0].z == -9999.99){

//     }
//     if(geometry[ROW - 1][COL - 1].z == -9999.99){

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

    // string output_path = "250_records_complimented.txt";
    string output_path = "53394640_dsm_1m_complimented.txt";

    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input1(geometry, file_in);
    output1(geometry, file_out);

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;
}