#include"geometry_points.h"
int main()
{
    system_clock::time_point start_time, end_time;
    start_time = system_clock::now();

    string input_path = "53394640_dsm_1m.dat";

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

    input_raw(geometry, file_in);
  
    complement(geometry);
    
    distinguish(geometry);

    vector<vector<Point>> removed((ROW - 2) / 3, vector<Point>((COL - 2) / 3));

    remove(geometry, removed);

    smoothing(removed);

    output_removed(removed, file_out); 
    end_time = system_clock::now();
    cout << duration_cast<nanoseconds>(end_time - start_time).count() << " nanosec" << endl;
}