// compliment lack points
#include<iostream>
#include<fstream>
#include<vector>

#define X 100
#define Y 100

using namespace std;

struct Point{
    double x;
    double y;
    double z;
    bool isBuilding = true; //建物ラベルとして初期化
};

int main()
{
    string filename = "53394640_dsm_1m.dat";
    ifstream file_in{filename}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "ファイルを開けません："<< filename << "\n";
        exit(1);
    }
    vector<vector<Point>> geometry(X, vector<Point>(Y));
    string line;

}