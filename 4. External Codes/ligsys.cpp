#include<bits/stdc++.h>
#define task "ligsys"
using namespace std;

const int mn=1e3+11,mod=111539786;

void add(int& a,const int& b){
    a+=b;if(a>=mod)a-=mod;
}
int prod(int a,int b){
    return 1LL*a*b%mod;
}

int n,m,s,k;
int dp[mn][mn],DP[mn][mn];

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #else
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    #endif
    cin>>n>>m>>s>>k;

    dp[0][0]=1;
    for(int i=0;i<=s;i++)
        for(int j=0;j<=i && j<=n;j++)if(dp[i][j]){
            if(j<n)add(dp[i+1][j+1],prod(dp[i][j],n-j));
            if(j>0)add(dp[i+1][j-1],prod(dp[i][j],j));
        }

    DP[0][0]=1;
    for(int i=0;i<=s;i++)
        for(int j=0;j<=i && j<=m;j++)if(DP[i][j]){
            if(j<m)add(DP[i+1][j+1],prod(DP[i][j],m-j));
            if(j>0)add(DP[i+1][j-1],prod(DP[i][j],j));
        }

    int res=0;
    for(int x=0;x<=n;x++)
        for(int y=0;y<=m;y++)if(x*m+y*n-2*x*y==k){
            add(res,prod(dp[s][x],DP[s][y]));
        }
    
    return cout<<res,0;
}