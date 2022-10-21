// remove points
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

void input3(vector<vector<Point>>& geometry, ifstream& file_in)
{   
    for (int i = 308; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
    }
}

// write points to file
void output3(vector<vector<Point>>& geometry, ofstream& file_out)
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
    // string input_path = "250_records_distinguished.txt";
    string input_path = "53394640_dsm_1m_distinguished.txt";

    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }

    // string output_path = "250_records_removed.txt";
    string output_path = "53394640_dsm_1m_removed.txt";

    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input3(geometry, file_in);
    output3(geometry, file_out);

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;
}