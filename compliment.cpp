// compliment lack points
#include<iostream>
#include<fstream>
#include<vector>
#define X 100
#define Y 100

struct Point{
    double x;
    double y;
    double z;
    bool flag = 0; //建物ラベルとして初期化
};

int main()
{
    std::string filename = "53394640_dsm_1m.dat";
    std::ifstream file_in{filename}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        std::cerr << "ファイルを開けません："<< filename << "\n";
        std::exit(1);
    }
    std::vector<std::vector<Point>> geometry(X, std::vector<Point>(Y));
    std::string line;

}