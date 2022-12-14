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
    
    //ここでエリアの行数と列数を求める
    int row,col;
    row=geometry.size();//行数の取得
    col=geometry[0].size();//列数の取得
    int i,j,k,l,n=10,limit,av_sr=0,av_sm=0;//nは分割数(9なら3)
    int nrow=row/n;//行数を均等に分割
    int ncol=col/n;//列数を均等に分割
    int arow=row%n;//あまり
    int acol=col%n;//あまり
    int p_n_row=nrow,p_n_col=ncol;//現在いるエリアの列数,行数
    int srow=0,scol=0;//どこまで行列を使用したか(geometryからjgeometryへの代入操作時に必要)
    int end[310][380]={0};//探索済みの印
    double sumz=0,summ=0;
    vector<vector<Point>> jgeometry(nrow+arow,vector<Point>(ncol+acol));
    for(k=0; k<n; k++){
        if(k==n-1) p_n_row+=arow;
        for(l=0; l<n; l++){
             if(l==n-1) p_n_col+=acol;
             for(i=0; i<p_n_row; i++){
                    for(j=0; j<p_n_col; j++){
                        jgeometry[i][j]=geometry[i+srow][j+scol];
                        if(geometry[i+srow][j+scol].z<=15&&geometry[i+srow][j+scol].z>5){
                        summ+=geometry[i+srow][j+scol].z;
                        av_sm++;
                        }
                        if(geometry[i+srow][j+scol].z<=25&&geometry[i+srow][j+scol].z>15){
                        sumz+=geometry[i+srow][j+scol].z;
                        av_sr++;
                        }
                    }
    }

    //上限値の決定
    if(av_sr!=0){
        limit=sumz/av_sr+3;
    }
    else if(av_sm!=0){
        limit=summ/av_sm+3;
    }else{
        limit=0;
    }
        for(i=0; i<p_n_row; i++){
            for(j=0; j<p_n_col; j++){
                end[i][j]=0;
            }
        }
       
        for(i=0; i<p_n_row; i++){
            for(j=0; j<p_n_col; j++){
                if(jgeometry[i][j].z<=limit&&jgeometry[i][j].isBuilding==1&&end[i][j]==0){
                    judge(jgeometry,i,j,p_n_row,p_n_col,limit,end);
                }
            }
        }
        for(i=0; i<p_n_row; i++){
            for(j=0; j<p_n_col; j++){
                geometry[i+srow][j+scol]=jgeometry[i][j];
            }
        }
            scol+=p_n_col;
            sumz=0;
            summ=0;
            av_sr=0;
            av_sm=0;
            if(l==n-1) p_n_col-=acol;
            }
            if(k==n-1) p_n_row-=arow;
            scol=0;
            srow+=p_n_row;
    }

    vector<vector<Point>> removed((ROW - 2) / 3, vector<Point>((COL - 2) / 3));

    remove(geometry, removed);

    smoothing(removed);

    output_removed(removed, file_out); 
    end_time = system_clock::now();
    cout << duration_cast<nanoseconds>(end_time - start_time).count() << " nanosec" << endl;
}