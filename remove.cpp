// remove points
#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<cmath>
#include<algorithm>

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
void input_distinguished(vector<vector<Point>>& geometry, ifstream& file_in)
{   
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            file_in >> geometry[i][j].x >> geometry[i][j].y >> geometry[i][j].z >> geometry[i][j].isBuilding;
        }
    }
}

// write points to file
void output_removed(vector<vector<Point>>& removed, ofstream& file_out)
{
    int r = int(removed.size());
    int l = int(removed[0].size());
    for(int i = 0; i < r; ++i)
    {
        for(int j = 0; j < l; ++j)
        {
            file_out << removed[i][j].x << ' ' << removed[i][j].y << ' ' << removed[i][j].z << ' ' << removed[i][j].isBuilding << endl;
        }
    }
}

void smoothing(vector<vector<Point>>& removed)
{
    int row = int(removed.size());
    int col = int(removed[0].size());
    for(int i = 1; i < row - 1; ++row)
    {
        for(int j = 1; j < col - 1; ++col)
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
            }
            if(num_building < 9){
                removed[i][j].isBuilding = false;
                removed[i][j].z = min_height;
            }
        }
    }
}

// from 9 points to 1 point
void remove(vector<vector<Point>>& geometry, vector<vector<Point>>& removed)
{
    int row = 0;
    int col = 0;
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
                             + geometry[i + 2][j + 2].z * geometry[i + 2][j + 2].isBuilding)/num_building; // 建物点の平均値
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

int main()
{
    string input_path = "53394640_dsm_1m_distinguished.txt";

    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }

    string output_path = "53394640_dsm_1m_removed.txt";

    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }

    vector<vector<Point>> geometry(ROW, vector<Point>(COL));
    vector<vector<Point>> removed((ROW - 2) / 3, vector<Point>((COL - 2) / 3 + 1));

    input_distinguished(geometry, file_in);
    remove(geometry, removed);
    smoothing(removed);
    output_removed(removed, file_out);

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;
}