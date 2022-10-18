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

// read file and strage points as an array
void input(vector<vector<Point>>& geometry, ifstream& file_in)
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
void output(vector<vector<Point>>& geometry, ofstream& file_out)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_out << geometry[i][j].x << ' ' << geometry[i][j].y << ' ' << geometry[i][j].z << endl;
        }
    }
}

int main()
{
    string input_path = "250_records.txt";
    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "ファイルを開けません："<< input_path << "\n";
        exit(1);
    }

    string output_path = "250_records_out.txt";
    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_out){
        cerr << "ファイルを開けません："<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input(geometry, file_in);
    output(geometry, file_out);
}