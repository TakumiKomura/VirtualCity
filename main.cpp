#include"geometry_points.h"
int main()
{
    system_clock::time_point start_time, end_time, start_main, end_main;
    start_main = system_clock::now();

    string input_path = "53394640_dsm_1m.dat";
    ifstream file_in{input_path}; //-std=c++17でコンパイル可能（file_in)
    if(!file_in){
        cerr << "could not open file: "<< input_path << "\n";
        exit(1);
    }

    string output_path = "53394640_dsm_1m_removed.dat";
    ofstream file_out{output_path}; //-std=c++17でコンパイル可能（file_out)
    if(!file_out){
        cerr << "could not open file: "<< output_path << "\n";
        exit(1);
    }
    vector<vector<Point>> geometry(ROW, vector<Point>(COL));

    input_raw(geometry, file_in);

    start_time = system_clock::now();
    complement(geometry);   
    end_time = system_clock::now();
    cout << "complemtnt: " << duration_cast<nanoseconds>(end_time - start_time).count() << " nanosec" << endl;

    start_time = system_clock::now();
    distinguish(geometry);
    end_time = system_clock::now();
    cout << "distinguish: " << duration_cast<nanoseconds>(end_time - start_time).count() << " nanosec" << endl;

    start_time = system_clock::now();
    vector<vector<Point>> removed((ROW - 2) / 3, vector<Point>((COL - 2) / 3));
    remove(geometry, removed);
    end_time = system_clock::now();
    cout << "remove: " << duration_cast<nanoseconds>(end_time - start_time).count() << " nanosec" << endl;

    start_time = system_clock::now();
    smoothing(removed);
    end_time = system_clock::now();
    cout << "smoothing: " << duration_cast<nanoseconds>(end_time - start_time).count() << " nanosec" << endl;

    output_removed(removed, file_out); 

    end_main = system_clock::now();
    cout << "main: " << duration_cast<nanoseconds>(end_main - start_main).count() << " nanosec" << endl;
}