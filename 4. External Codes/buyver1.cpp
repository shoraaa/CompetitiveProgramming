#include <bits/stdc++.h>
using namespace std;
int n,m,C[1002],vs[1002],num[1002];
vector <int> root,A[1002];
long long dp[1002][1002][3];

void dfs(int u)
{
    vs[u]=1;num[u]=1;
    dp[u][0][0]=0;dp[u][1][1]=C[u];
    for (int i=0;i<A[u].size();i++)
    {
        int v=A[u][i];
        if (vs[v]==1) continue;
        dfs(v);
        num[u]+=num[v];
        for (int j=num[u];j>=1;j--)
            for (int l=0;l<=min(num[v],j);l++)
            {
                dp[u][j][0]=min(dp[u][j][0],dp[u][j-l][0]+min(dp[v][l][0],dp[v][l][2]));
                dp[u][j][1]=min(dp[u][j][1],dp[u][j-l][1]+min(dp[v][l][0],dp[v][l][1]));
                dp[u][j][2]=min(dp[u][j][2],dp[u][j-l][2]+min(dp[v][l][0],dp[v][l][1]));
                dp[u][j][2]=min(dp[u][j][2],dp[u][j-l][1]+min(dp[v][l][1],dp[v][l][2]));
            }
    }
}

void solve()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        cin>>C[i];
    for (int i=1;i<=m;i++)
    {
        int a,b;cin>>a>>b;
        A[a].push_back(b);
        A[b].push_back(a);
    }
    for (int i=0;i<=n;i++)
        for (int j=0;j<=n;j++)
            for (int l=0;l<3;l++)
                dp[i][j][l]=1e18;
    for (int i=1;i<=n;i++)
    {
         A[0].push_back(i);
    }
    dfs(0);
    
    int q;cin>>q;
    while (q--)
    {
        long long s;cin>>s;
        if (s<dp[0][2][0]) {cout<<0<<'\n';continue;}
        int d=2;int c=n;int res=0;
        while (d<=c)
        {
            int mid=(d+c)/2;
            if (s>=dp[0][mid][0]) {res=mid;d=mid+1;}
            else c=mid-1;
        }
        cout<<res<<'\n';
    }
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("buyver.in","r",stdin);
    // freopen("buyver.out","w",stdout);
    solve();
}

