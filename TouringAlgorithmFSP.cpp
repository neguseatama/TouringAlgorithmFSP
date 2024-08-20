/*
Touring Algorithm (Fixed the starting point) in C++
C++による（始点を固定した）巡回アルゴリズム
https://neguse-atama.hatenablog.com
*/

//1番目に与えられた座標を始点とする.
#include<bits/stdc++.h>
using namespace std;

int n; //地点の数
long double spot[20][2]; //各地点の座標
int route[20]; //巡回経路

//経路の中の２か所の順番を交換
void Swap(int a,int b){
    int t=route[a];
    route[a]=route[b];
    route[b]=t;
}

//経路初期化(入力された順)
void init(){
    for(int i=0;i<n;i++){
        route[i]=i;
    }
}

//2点間の距離を求める
long double DistPP(int a,int b){
    long double x=spot[a][0]-spot[b][0];
    long double y=spot[a][1]-spot[b][1];
    return sqrt(x*x+y*y);
}

//経路が変わることで距離が短縮されるかの判定と,
//短縮される場合は経路変更.
bool TF(int a,int b){
    bool tf=false;
    long double dif = DistPP(route[a%n],route[(a+1)%n])
                +DistPP(route[b%n],route[(b+1)%n])
                -DistPP(route[a%n],route[b%n])
                -DistPP(route[(a+1)%n],route[(b+1)%n]);
    if(dif>0){
        for(int i=0;i<(b-a)/2;i++){
            Swap((a+1+i)%n,(b-i)%n);
        }
        tf=true;
    }
    return tf;
}

//2-Opt法メイン
//距離の短縮ができるポイントがなくなるまで経路変更の繰り返し.
void Opt(){
    bool tf=true;
    while(tf==true){
        tf=false;
        for(int i=0;i<n;i++){
            for(int j=i+2;j<i+n-1;j++){
                if(TF(i,j)==true){
                    tf=true;
                }
            }
        }
    }
}

//経路・総距離出力
void Print(){
    
    int start=-1;
    for(int i=0;i<n;i++){
        if(route[i]==0){
            start=i;
        }
    }
    for(int i=start;i<n;i++){
        cout<<route[i]+1<<" ";
    }
    for(int i=0;i<start;i++){
        cout<<route[i]+1<<" ";
    }
    
    cout<<"\nTotal Distance : ";
    long double dist=0.0;
    for(int i=0;i<n;i++){
        dist+=DistPP(route[i],route[(i+1)%n]);
    }
    int num=(start==0 ? n-1 : start-1);
    dist-=DistPP(route[start],route[num]);
    cout<<fixed<<setprecision(15)<<dist<<"\n\n";
    
}

//入出力
int main(void){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>spot[i][0]>>spot[i][1];
        cout<<i+1<<"(";
        cout<<fixed<<setprecision(5)<<spot[i][0]<<",";
        cout<<fixed<<setprecision(5)<<spot[i][1]<<")"<<endl;
        //各地点の座標を入力し、
        //それぞれに番号をふって出力.
    }
    cout<<endl;
    
    init();
    
    cout<<"First Route :\n";
    Print();
    
    Opt();
    
    cout<<"Optimization Route :\n";
    Print();
    
    return 0;
}