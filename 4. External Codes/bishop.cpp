#include<bits/stdc++.h>
using namespace std;
struct data {
	int u,v;
};

const int N = 5004, oo = 1e9 + 7;
int n,m, stX, stY, fiX, fiY;
queue<data> dq;
int d[N][N];
int h[4] = { -1, 1, 1, -1 }, c[4] = { 1, 1, -1, -1 };
inline void Read(int &val){
	val = 0; char c;
	do { c = getchar(); } while (!isdigit(c));
	while (isdigit(c)) { val = val * 10 + c - '0'; c = getchar(); }
}
void solve(){
    d[stX][stY]=1;
    dq.push({stX,stY});
    while(!dq.empty()){
        data top=dq.front();dq.pop();
        int u=top.u,v=top.v;
        if (u==fiX && v==fiY){cout<<d[u][v]-1;exit(0);}
        for (int nDir=0;nDir<4;++nDir){
            int x = u , y = v ;
            while(true){
                x+=h[nDir];y+=c[nDir];
                if (x < 1 || x > n || y < 1 || y > n || d[x][y]==-1 || (d[x][y]<=d[u][v] && d[x][y]!=0)) break;
                d[x][y] = d[u][v] + 1;
                dq.push({x,y});
            }
        }
    }
    cout<<-1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("nhap.inp","r")){
        freopen("nhap.inp","r",stdin);
        freopen("nhap.out","w",stdout);
    }
    else{
        freopen("bishop.inp","r",stdin);
        freopen("bishop.out","w",stdout);
    }
    Read(n);Read(m);
    Read(stX);Read(stY);Read(fiX);Read(fiY);
    while(m--){
        int x,y;
        Read(x);Read(y);
        d[x][y]=-1;
    }
    solve();
}
