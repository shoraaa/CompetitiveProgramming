///cong thuc euler: F = E-V+C+1
///__builtin_popcount
///
#define X first
#define Y second
#define pb push_back
#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int randint(int l,int r){
    return uniform_int_distribution < int > (l,r) (rng);
}
///shuffle(a.begin(), a.end(), rng)
#define int long long
const int MAX=1e5+4,inf=1e16,M2=5e5+3;
void maxx(int &a,int b){if(b>a) a=b;}
void minn(int &a,int b){if(b<a) a=b;}
template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}
bool cmax(int &a,int b){
    if(b>a){a=b;return 1;} else return 0;
}
typedef pair < int, int > ii;

vector < int > pr[MAX];
struct qb{
    int a,b;
    int c;
    qb(int a,int b,int c): a(a),b(b),c(c) {};
};

int C[MAX],W[MAX],B[MAX];
ii ST[20][MAX];
int LG[MAX];
int getm(int u,int v){
    int z=LG[v-u+1];
    return min(ST[z][u],ST[z][v-(1<<z)+1]).Y;
}
int ans=0;
void dfs(int L,int R){
    int v=getm(L,R);
    /// getm L R -> lay phan tu v tu L den R co Cv-Wv nho nhat
    maxx(ans,C[v]+B[R]-B[L-1]);
    if(L!=v)dfs(L,v-1);
    if(v!=R)dfs(v+1,R);
}
void GO(int L,int R){
    int v=R+1;
    int lim=ans-(B[R]-B[L-1]);
    for(int i=16;i>=0;i--)
    if(v>(1<<i) && ST[i][v-(1<<i)].X>lim) v-=(1<<i);
    v--;
    if(v<L || C[v]>lim){cout<<"WA";exit(0);}
    //if(v!=R)
    cout<<v<<' ';
    if(L!=v)GO(L,v-1);
    if(v!=R)GO(v+1,R);
}
ii a[MAX];
signed main(){
    ///g++ grader.cpp .cpp -std=c++14 -O2 -Wl,--stack,10485760
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("QBST.inp","r",stdin);
    //freopen("bao.out","w",stdout);
    int n,m;
    cin>>n;
    for(int i=2;i<=n;i++)LG[i]=LG[i>>1]+1;
    for(int i=1;i<=n;i++) cin>>C[i];
    for(int i=1;i<=n;i++) cin>>W[i];
    for(int i=1;i<=n;i++){
        C[i]-=W[i];B[i]=B[i-1]+W[i];
        ST[0][i]=ii(C[i],i);
    }
    int M=0;
    for(int j=1;j<17;j++){
        for(int i=1;i<=n-(1<<j-1);i++){
            ST[j][i]=min(ST[j-1][i],ST[j-1][i+(1<<j-1)]);
        }
    }
    /// de quy 1 tham lam tim dap an
    dfs(1,n);
    //cout<<getm(1,n)<<'\n';
    /// ans
    cout<<ans<<'\n';
    ///lay cay co thu tu tu dien tot nhat
    GO(1,n);

}


