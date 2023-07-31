#include <bits/stdc++.h>
using namespace std;
int m,n,s,t,ss,tt;
int A[102][102],C[205][205],F[205][205],vs[205],trace[205];
void bfs()
{
    queue <int> q;
    q.push(s);vs[s]=1;
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for (int v=1;v<=m+n+4;v++)
            if (vs[v]==0&&v!=u&&C[u][v]>F[u][v])
            {
                trace[v]=u;
                vs[v]=1;
                q.push(v);
                if (v==t) return;
            }
    }
}
int dem;
int num1=0;
void increase_flow()
{
    int v=t;
    int minc=1e9;
    while (v!=s)
    {
        int u=trace[v];
        minc=min(minc,C[u][v]-F[u][v]);
        v=u;
    }
    dem+=minc;
    v=t;
    while (v!=s)
    {
        int u=trace[v];
        F[u][v]+=minc;
        F[v][u]-=minc;
        v=u;
    }
}
int check(int k)
{
    memset(C,0,sizeof(C));
    memset(F,0,sizeof(F));
    int need=0;
    for (int i=1;i<=m;i++)
    {
        int numstar=0;int num0=0;int num1=0;
        for (int j=1;j<=n;j++)
        {
            numstar+=(A[i][j]==2);
            num0+=(A[i][j]==0);
            num1+=(A[i][j]==1);
        }
        int l=numstar+1;int r=-1;
        for (int j=0;j<=numstar;j++)
            if (abs(num1+j-num0-(numstar-j))<=k)
        {
            r=max(r,j);
            l=min(l,j);
        }
        r+=num1;l+=num1;
        if (r<l) return 0;
        C[ss][i]=r-l;
        C[ss][t]+=l;
        C[s][i]+=l;
        need+=l;
    }
    C[tt][ss]=1e9;
    for (int i=1;i<=n;i++)
    {
        int numstar=0;int num0=0;int num1=0;
        for (int j=1;j<=m;j++)
        {
            numstar+=(A[j][i]==2);
            num0+=(A[j][i]==0);
            num1+=(A[j][i]==1);
        }
        int l=numstar+1;int r=-1;
        for (int j=0;j<=numstar;j++)
            if (abs(num1+j-num0-(numstar-j))<=k)
        {
            r=max(r,j);
            l=min(l,j);
        }
        r+=num1;l+=num1;
        if (r<l) return 0;
        C[i+m][tt]=r-l;
        C[i+m][t]+=l;
        C[s][tt]+=l;
        need+=l;
    }
   // cout<<need<<endl;
    for (int i=1;i<=m;i++)
        for (int j=1;j<=n;j++)
        if (A[i][j]>0)
    {
        if (A[i][j]==1)
        {
            C[i][j+m]=0;
            C[i][t]++;
            C[s][j+m]++;
            need++;
        }
        else C[i][j+m]=1;
    }
    dem=0;
    while (true)
    {
        memset(vs,0,sizeof(vs));
        bfs();
        if (vs[t]==0) break;
        else increase_flow();
    }
   // cout<<k<<' '<<dem<<' '<<need<<endl;
    if (dem==need) return 1;
    else return 0;
}
void solve()
{
    cin>>m>>n;
    s=m+n+1;t=m+n+2;
    ss=m+n+3;tt=m+n+4;
    for (int i=1;i<=m;i++)
        for (int j=1;j<=n;j++)
    {
        char x;cin>>x;
        if (x=='0') A[i][j]=0;
        if (x=='1') A[i][j]=1;
        if (x=='*') A[i][j]=2;
        if (A[i][j]==1) num1++;
    }
    int d=0;int c=max(m,n);
    int res=0;;
    while (d<=c)
    {
        int mid=(d+c)/2;
        if (check(mid))
        {
            c=mid-1;
            res=mid;
        }
        else d=mid+1;
    }
    cout<<res;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    freopen("star.inp","r",stdin);
    freopen("star.out","w",stdout);
    solve();
}
