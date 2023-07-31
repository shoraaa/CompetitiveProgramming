
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
int n,m,k,s,t;
typedef pair<int,int> II;
int id;
int64_t d[maxn];
vector<int> g[maxn];
int dd[maxn],cl[maxn];
int M;
vector<II> adj[maxn];

struct edge
{
    int dau,cuoi,flow,cap;
    int w;
};

edge e[maxn];


bool  Butter()
{
    queue<int> q;
    for(int i=1;i<=n+2;i++) d[i]=2e18,dd[i]=0;
    q.push(s);
    dd[s]=1;
    d[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        dd[u]=0;
        for(int i:g[u])
        {
            int v=e[i].cuoi;
            int l=(e[i].flow>=0)?e[i].w:-e[i].w;
            if(e[i].flow<e[i].cap&&d[u]+l<d[v])
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

    return (d[t]!=2e18);
}
int Bloss(int u,int val)
{
    if(u==t) return val;
    if(cl[u]==id) return 0;
    cl[u]=id;
    for(int i:g[u])
    {
        int v=e[i].cuoi;
        int l=(e[i].flow>=0) ?e[i].w:-e[i].w;
        if(cl[v]!=id&&d[v]==d[u]+l)
            if(e[i].cap>e[i].flow)
        {
            if(int del=Bloss(v,min(val,e[i].cap-e[i].flow)))
            {
                e[i].flow+=del;
                e[2*m+1-i].flow-=del;
                return del;
            }
        }
    }
    return 0;
}
int64_t mf=0;
int64_t Sandman()
{

    mf=0;
    id=0;
    //cout<<Butter()<<endl;
    while(Butter())
    {
        //if(!Butter()) break;
        //cout<<111<<endl;
        while(int del=(++id,Bloss(s,k-mf)))
        {
            mf+=del;
           // if(mf==k) break;
        }
        ///cout<<111<<endl;
    }


    int64_t cost=0;
    for(int u=1;u<=n;u++)
        for(int i:g[u])
    {
        int v=e[i].cuoi;
        int L=e[i].w;
        if(e[i].flow>0)
            cost+=L;
    }
    return cost;
}
int degin[maxn],degout[maxn];
int tmp1[maxn],tmp2[maxn],sz1,sz2;
int kc[maxn];
set<II> ss;

void dij(int xp)
{
    for(int i=1;i<=n;i++)
       kc[i]=2e9;
    ss.clear();
    kc[xp]=0;
    ss.insert({0,xp});
    while(!ss.empty())
    {
        II P=*ss.begin();
        ss.erase(P);
        int u=P.second;
        for(II x:adj[u])
        {
            int v=x.first,l=x.second;
            if(kc[v]>kc[u]+l)
            {
                if(kc[v]!=2e9)
                ss.erase({kc[v],v});
                kc[v]=kc[u]+l;
                ss.insert({kc[v],v});
            }
        }
    }
}

void Bubbles()
{
    scanf("%d%d",&n,&M);
    k=1e9,s=n+1,t=n+2;

    int64_t sum=0;

    for(int i=1;i<=M;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        sum+=w;
        degout[u]++;
        degin[v]++;
        adj[u].push_back({v,w});
    }

    for(int i=1;i<=n;i++)
    {
        if(degin[i]>degout[i])
        {
            tmp1[++sz1]=i;
        }
        else if(degin[i]<degout[i])
        {
            tmp2[++sz2]=i;

        }
    }

    for(int i=1;i<=sz1;i++)
    {
        int u=tmp1[i];
        dij(u);
        for(int j=1;j<=sz2;j++)
        {
            ++m;
            int v=tmp2[j];
            e[m].dau=u;
            e[m].cuoi=v;
            e[m].cap=1e9;
            e[m].flow=0;
            e[m].w=kc[v];
        }
    }

    for(int i=1;i<=sz1;i++)
    {
        int u=tmp1[i];
        ++m;
        e[m].dau=s;
        e[m].cuoi=u;
        e[m].cap=degin[u]-degout[u];
        e[m].flow=0;
        e[m].w=0;
    }

    for(int i=1;i<=sz2;i++)
    {
        int u=tmp2[i];
        ++m;
        e[m].dau=u;
        e[m].cuoi=t;
        e[m].cap=degout[u]-degin[u];
        e[m].flow=0;
        e[m].w=0;
    }

    for(int i=1;i<=m;i++)
    {
        int j=2*m+1-i;
        e[j].dau=e[i].cuoi;
        e[j].cuoi=e[i].dau;
        e[j].cap=0;
        e[j].flow=0;
        e[j].w=0;
    }

    for(int i=1;i<=2*m;i++)
    {
        int u=e[i].dau;
        g[u].push_back(i);
    }

    cout<<Sandman()+sum;

    //cout<<Butter();
    //cout<<tmp1[1]<<" "<<tmp2[1];

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
