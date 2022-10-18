// compliment lack points
#include<iostream>
#include<fstream>
#include<vector>

#define ROW 5
#define COL 50

using namespace std;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
};

int main()
{
    string filename = "250_records.txt";
    ifstream file_in{filename}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "ファイルを開けません："<< filename << "\n";
        exit(1);
    }
    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    // 点の格納
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z;
        }
    }

    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            cout << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << endl;
        }
    }
}