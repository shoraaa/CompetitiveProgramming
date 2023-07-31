#include <bits/stdc++.h>
#define maxn 1111111
#define Optimus "dcpp"
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

int n,m,s,t;
int c[1111][1111],f[1111][1111];
typedef pair<int,int64_t> II;
vector<II> g[maxn];
vector<II> adj[maxn];
int in[maxn],out[maxn];
int tmp1[maxn],tmp2[maxn],sz1,sz2;
int64_t kc[maxn];


void dij(int xp)
{
    set<pair<int64_t,int> > q;
    for(int i=1;i<=n;i++)
        kc[i]=2e18;
    kc[xp]=0;
    q.clear();
    q.insert({0,xp});

    while(!q.empty())
    {
        pair<int64_t,int> P=*q.begin();
        q.erase(P);
        int u=P.second;
        for(II x:g[u])
        {
            int v=x.first,l=x.second;
            if(kc[v]>kc[u]+l)
            {
                if(kc[v]!=2e18)
                q.erase({kc[v],v});
                kc[v]=kc[u]+l;
                q.insert({kc[v],v});
            }
        }
    }
}

int64_t d[maxn];
int dd[maxn];int cl[maxn],id;

bool bfs()
{
    queue<int> q;
    for(int i=1;i<=n+2;i++)
        d[i]=1e18,dd[i]=0;
    d[s]=0;
    dd[s]=1;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        dd[u]=0;

        for(II x:adj[u])
        {
            int v=x.first;

            int64_t l=(f[u][v]>=0) ?x.second:-x.second;

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

    return (d[t]!=1e18);
}

int fins(int u,int val)
{
    if(u==t) return val;
    if(cl[u]==id) return 0;
    cl[u]=id;
    for(II x:adj[u])
    {
        int v=x.first;
        int64_t l=(f[u][v]>=0)?x.second:-x.second;
        if(cl[v]!=id&&d[v]==d[u]+l)
            if(c[u][v]>f[u][v])
        {
            if(int del=fins(v,min(val,c[u][v]-f[u][v])))
            {
                f[u][v]+=del;
                f[v][u]-=del;
                return del;
            }
        }

    }
    return 0;
}

int64_t cal()
{
    int mf=0;
    id=0;
    while(bfs())
    {

        while(int del=(++id,fins(s,1e9)))
            mf+=del;

    }

    int64_t cost=0;
    for(int u=1;u<=n;u++)
        for(II x:adj[u])
    {
        int v=x.first;
        int64_t l=x.second;
        if(f[u][v]>0)
            cost+=l;
    }
    return cost;
}

void Bubbles()
{
    cin>>n>>m;

    s=n+1,t=n+2;
    int64_t sum=0;

    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        sum+=w;
        out[u]++,in[v]++;
        g[u].push_back({v,w});
    }

    for(int i=1;i<=n;i++)
    {
        if(in[i]-out[i]>0)
        {
            tmp1[++sz1]=i;
        }
        else if(in[i]-out[i]<0)
            tmp2[++sz2]=i;
    }

    for(int i=1;i<=sz1;i++)
    {
        int u=tmp1[i];
        dij(u);
        for(int j=1;j<=sz2;j++)
        {
            int v=tmp2[j];
            c[u][v]=1e9;
            adj[u].push_back({v,kc[v]});
            adj[v].push_back({u,kc[v]});

        }
    }

    for(int i=1;i<=sz1;i++)
    {
        int u=tmp1[i];
        c[s][u]=in[u]-out[u];
        adj[s].push_back({u,0});
        adj[u].push_back({s,0});
    }

    for(int i=1;i<=sz2;i++)
    {
        int u=tmp2[i];
        c[u][t]=out[u]-in[u];
        adj[u].push_back({t,0});
        adj[t].push_back({u,0});
    }

    cout<<cal()+sum;
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
