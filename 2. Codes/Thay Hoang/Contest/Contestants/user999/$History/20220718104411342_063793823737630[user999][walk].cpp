#include <bits/stdc++.h>
#define maxn 1111111
#define Optimus "walk"
#define X first
#define Y second
#define N 3400000
#define maxh 100000
#define mod 123456789
#define moe 1000000007
//#define B 331
using namespace std;
//    /\          /\
//   /  \        /  \
//  /    \______/    \
// |                  |
// |  ---       ---   |
// |                  |
//  \       -        /
int n,m,k,s,t;
typedef pair<int,int> II;
int c[1212][1232],f[1221][1212];
int id;
int64_t d[maxn];
vector<II> g[maxn];
int dd[maxn],cl[maxn];
bool  Butter()
{
    queue<int> q;
    for(int i=1;i<=n;i++) d[i]=1e9,dd[i]=0;
    q.push(s);
    dd[s]=1;
    d[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        dd[u]=0;
        for(II x:g[u])
        {
            int v=x.first;
            int l=(f[u][v]>=0)?x.second:-x.second;
            if(f[u][v]<c[u][v]&&d[u]+l<d[v])
            {
                d[v]=d[u]+l;
                if(dd[v]==0)
                {
                    q.push(v);
                    dd[v]=1;
                }
            }
        }
    }
    return (d[t]!=1e9);
}
int Bloss(int u,int val)
{
    if(u==t) return val;
    if(cl[u]==id) return 0;
    cl[u]=id;
    for(II x:g[u])
    {
        int v=x.first;
        int l=(f[u][v]>=0) ?x.second:-x.second;
        if(cl[v]!=id&&d[v]==d[u]+l)
            if(c[u][v]>f[u][v])
        {
            if(int del=Bloss(v,min(val,c[u][v]-f[u][v])))
            {
                f[u][v]+=del;
                f[v][u]-=del;
                return del;
            }
        }
    }
    return 0;
}
int mf=0;
int64_t Sandman()
{

    mf=0;
    id=0;
    while(mf<k)
    {
        if(!Butter()) return -1;
        while(int del=(++id,Bloss(s,k-mf)))
        {
            mf+=del;
            if(mf==k) break;
        }
    }
    if(mf<k) return -1;
    int64_t cost=0;
    for(int u=1;u<=n;u++)
        for(II x:g[u])
    {
        int v=x.first;
        int L=x.second;
        if(f[u][v]>0)
            cost+=L;
    }
    return cost;
}
void Bubbles()
{
    scanf("%d%d",&n,&m);
    k=2,s=1,t=n;
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back({v,w});
        g[v].push_back({u,w});
        c[u][v]=1;
        c[v][u]=1;
    }
    int64_t ds=Sandman();
    cout<<ds<<"\n";
    if(ds==-1) return;

    vector<int> ans;
    for(int i=1;i<=k;i++)
    {
        vector<int> path;
        path.push_back(s);
        int u=s;
        while(u!=t)
        {
            for(II x:g[u])
            {
                int v=x.first;
                if(f[u][v]==1)
                {
                    path.push_back(v);
                    f[u][v]=0;
                    u=v;
                    break;
                }
            }
        }
        if(i==1)
        for(int u:path) ans.push_back(u);
        else
        {
            ans.pop_back();
            reverse(path.begin(),path.end());
            for(int u:path) ans.push_back(u);
        }
    }
    for(int u:ans) cout<<u<<" ";
}
int main()
{
    if(fopen(Optimus".inp","r"))
    {
        freopen(Optimus".inp","r",stdin);
        freopen(Optimus".out","w",stdout);
    }
  Bubbles();
}
