//distinguish ground points from building points
#include<iostream>
#include<cmath>
#include<vector>
struct Point{
        int x;
        int y;
        int z;
};

void judge(std::vector<std::vector<Point>> geometry,int startrow,int startcol)
{
    
    int pastrow[10000];//1つ前の点の行の添え字
    int pastcol[10000];//1つ前の点の列の添え字
    int end[10000][10000];//探索済みの印
    int flag[10000][10000];//地面建物フラグ
    int row=startrow;//行
    int col=startcol;//列
    int n=0,completed=0;//繰り返し文に必要なフラグ
    while(completed==0){
         if(row==startrow&&col==startcol){//探索地点がスタート地点まで戻った時の処理
            for(int i=-1; i<1; i++){
                for(int j=-1; j<1; j++){
                    if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=0.5&&end[row+i][col+j]==0){
                    break;//まだ探索できる点があった
                    }
                    if(i=2&&j==2){
                        completed=1;//隣接点はすべて探索していた
                    }
                }
            }
         }
         if(completed==1) break;
         int i;
        for(i=0; i<8; i++){
            //隣接点走査
            for(int j=0; j<8; j++){
            if(std::fabs(geometry[row+i][col+j].z-geometry[row][col].z)<=0.5&&flag[row+i][col+j]!=0){
                //地面判定できる点があった
                pastrow[n]=row;
                pastcol[n]=col;//1つ前の行列の添え字
                n++;
                row=row+i;//次の点の行列の添え字
                col=col+j;
                flag[row][col]=0;//地面であることの更新
                break;
            }
            }
        }
        if(i==8){
            //隣接点を走査したが地面判定された点はなかった時
            end[row][col]=1;//隣接点が地面でないことをすべて確認した印
            judge(geometry,pastrow[n-1],pastcol[n-1]);//1つ前の点に戻って走査を再開する
            pastrow[n]=0;//使用済みの添え字を0にする
            pastcol[n]=0;
            n--;
            //pastの1番後ろの要素を削除する
        }
    }
}

/*深さ優先探索
#エリアごとに分割し、そのエリア内の一番低い点を探す
#エリアフラグを参照し、エリアごとに処理
#flag=0は地面、1は建物
#今見ている点はnow
#探索済みを判断するフラグをendとする*/