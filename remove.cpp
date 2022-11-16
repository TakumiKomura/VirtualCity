// remove points
#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<cmath>
#include<algorithm>

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
void output_removed(vector<Point>& removed, ofstream& file_out)
{
    for (int i = 0; i < int(removed.size()); ++i)
    {
        file_out << removed[i].x << ' ' << removed[i].y << ' ' << removed[i].z << ' ' << removed[i].isBuilding << endl;
    }
}

double _mean(double val1, double val2, double val3, double val4)
{
    return (val1 + val2 + val3 + val4) / 2;
}

double mean(double val1, double val2, double val3, double val4)
{
    return (val1 + val2 + val3 + val4) / 4;
}

double median(double val1, double val2, double val3, double val4)
{
    double big1, big2, big3, small1, small2, small3;

    if(val1 > val2){
        big1 = val1;
        small1 = val2;
    }else{
        big1 = val2;
        small1 = val1;
    }

    if(val3 > val4){
        big2 = val3;
        small2 = val4;
    }else{
        big2 = val4;
        small2 = val3;
    }

    if(big1 > big2)
        small3 = big2;
    else
        small3 = big1;
    
    if(small1 > small2)
        big3 = small1;
    else
        big3 = small2;

    return (big3 + small3) / 2;
}

double closest_to_mean(double val1, double val2, double val3, double val4)
{
    double val[4] = {val1, val2, val3, val4};
    double mean = (val1 + val2 + val3 + val4) / 4;
    double min = fabs(val[0] - mean);
    int min_idx = 0;
    double tmp;
    for (int i = 1; i < 4; i++){
        tmp = fabs(val[i] - mean);
        if (tmp < min){
            min = tmp;
            min_idx = i;
        }
    }
    return val[min_idx];
}

void remove(vector<vector<Point>>& geometry, vector<Point>& removed)
{
    int count = -1;
    for (int i = 0; i < ROW - 1; i += 2)
    {
        for (int j = 0; j < COL - 1; j += 2)
        {
            count++;
            int num_building = geometry[i][j].isBuilding
                             + geometry[i][j + 1].isBuilding 
                             + geometry[i + 1][j].isBuilding 
                             + geometry[i + 1][j + 1].isBuilding;
            if (num_building == 2){
                removed[count].x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
                removed[count].y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
                removed[count].z = _mean(geometry[i][j].z * geometry[i][j].isBuilding,
                                        geometry[i][j + 1].z * geometry[i][j + 1].isBuilding, 
                                        geometry[i + 1][j].z * geometry[i + 1][j].isBuilding,
                                        geometry[i + 1][j + 1].z * geometry[i + 1][j + 1].isBuilding);
                removed[count].isBuilding = true;

                count++;
                removed[count].x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
                removed[count].y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
                removed[count].z = _mean(geometry[i][j].z * !geometry[i][j].isBuilding,
                                        geometry[i][j + 1].z * !geometry[i][j + 1].isBuilding, 
                                        geometry[i + 1][j].z * !geometry[i + 1][j].isBuilding,
                                        geometry[i + 1][j + 1].z * !geometry[i + 1][j + 1].isBuilding);
                removed[count].isBuilding = false;
            }else{
                removed[count].x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
                removed[count].y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
                removed[count].z = mean(geometry[i][j].z, geometry[i][j + 1].z, 
                                        geometry[i + 1][j].z, geometry[i + 1][j + 1].z);
                if ((num_building == 0) || (num_building == 1)){
                    removed[count].isBuilding = false;
                }else{
                    removed[count].isBuilding = true;
                }
            }
        }
    }
    removed.resize(count);
}

// void remove(vector<vector<Point>>& geometry, ofstream& file_out)
// {
//     for (int i = 0; i < ROW - 1; i += 2)
//     {
//         for (int j = 0; j < COL - 1; j += 2)
//         {
//             Point tmp;
//             int num_building = geometry[i][j].isBuilding
//                              + geometry[i][j + 1].isBuilding 
//                              + geometry[i + 1][j].isBuilding 
//                              + geometry[i + 1][j + 1].isBuilding;
//             if (num_building == 2){
//                 tmp.x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
//                 tmp.y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
//                 tmp.z = _mean(geometry[i][j].z * geometry[i][j].isBuilding,
//                                         geometry[i][j + 1].z * geometry[i][j + 1].isBuilding, 
//                                         geometry[i + 1][j].z * geometry[i + 1][j].isBuilding,
//                                         geometry[i + 1][j + 1].z * geometry[i + 1][j + 1].isBuilding);
//                 tmp.isBuilding = true;
//                 file_out << tmp.x << ' ' << tmp.y << ' ' << tmp.z << ' ' << tmp.isBuilding << endl;

//                 tmp.x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
//                 tmp.y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
//                 tmp.z = _mean(geometry[i][j].z * !geometry[i][j].isBuilding,
//                                         geometry[i][j + 1].z * !geometry[i][j + 1].isBuilding, 
//                                         geometry[i + 1][j].z * !geometry[i + 1][j].isBuilding,
//                                         geometry[i + 1][j + 1].z * !geometry[i + 1][j + 1].isBuilding);
//                 tmp.isBuilding = false;
//                 file_out << tmp.x << ' ' << tmp.y << ' ' << tmp.z << ' ' << tmp.isBuilding << endl;
//             }else{
//                 tmp.x = (geometry[i][j].x + geometry[i][j + 1].x) / 2;
//                 tmp.y = (geometry[i][j].y + geometry[i + 1][j].y) / 2;
//                 tmp.z = mean(geometry[i][j].z, geometry[i][j + 1].z, 
//                                         geometry[i + 1][j].z, geometry[i + 1][j + 1].z);
//                 if ((num_building == 0) || (num_building == 1)){
//                     tmp.isBuilding = false;
//                 }else{
//                     tmp.isBuilding = true;
//                 }
//                 file_out << tmp.x << ' ' << tmp.y << ' ' << tmp.z << ' ' << tmp.isBuilding << endl;
//             }
//         }
//     }
// }

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
    vector<Point> removed;
    removed.resize(ROW * COL);

    input_distinguished(geometry, file_in);
    // remove(geometry, file_out);
    remove(geometry, removed);
    output_removed(removed, file_out);

    // system_clock::time_point start, end;
    // start = system_clock::now();
    // end = system_clock::now();
    // cout << duration_cast<nanoseconds>(end - start).count() << " nanosec" << endl;
}