#include<iostream>
#include<chrono>
#include<fstream>
#include<vector>
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

int main()
{
    system_clock::time_point start, end;
    start = system_clock::now();

    string input_path = "53394640_dsm_1m.dat";

    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }
    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    //比較したい処理
    start = system_clock::now();
    
    // Point *trash;
    // trash = new Point[897];
    for (int j = 0; j < 897; ++j)
    {
        file_in >> geometry[0][j].x >> geometry[0][j].y >> geometry[0][j].z;
    }
    //delete[] trash;

    end = system_clock::now();
    cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;
}