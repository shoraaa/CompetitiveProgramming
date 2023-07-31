#include <bits/stdc++.h>
#define maxn 100005
#define inf 1e18+1
#define fi first
#define se second
using namespace std;
typedef pair <int,int> II;
int n, m, k, S, T, mf, id, cl[maxn], path[maxn];
int dd[maxn];
long long d[maxn], cost;
vector <int> g[maxn];
struct Edge
{
    int dau,cuoi,capa,flow,ts;
};
Edge E[4*maxn];
bool Ford_Bellman()
{
    queue <int> q;
    for(int i = 1 ; i <= n; i++)
        d[i] = inf, dd[i] = 0;
    d[S] = 0;
    dd[S] = 1;
    q.push(S);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        dd[u] = 0;
        for(int i: g[u])
        {
            int v = E[i].cuoi, l = (E[i].flow >= 0)? E[i].ts:-E[i].ts;
            if(E[i].flow < E[i].capa && d[u] + l < d[v])
            {
                d[v] = d[u] + l;
                if(dd[v] == 0)
                {
                    q.push(v);
                    dd[v] = 1;
                }
            }
        }
    }
    return d[T] != inf;
}

int FindPath(int u, int val)
{
    if(u == T)
        return val;
    if(cl[u] == id)
        return 0;
    cl[u] = id;
    for(int i:g[u])
    {
        int v = E[i].cuoi;
        int l = (E[i].flow >= 0) ? E[i].ts : -E[i].ts;
        if(cl[v] != id && d[v] == d[u] + l)
        {
            if(E[i].capa > E[i].flow)
            {
                if(int delta = FindPath(v,min(val,E[i].capa - E[i].flow)))
                {
                    E[i].flow += delta;
                    E[4*m-i].flow -= delta;
                    return delta;
                }
            }
        }
    }
    return 0;
}

bool MinCost()
{
    cost = 0;
    mf = 0;
    id = 0;
    while(mf < k)
    {
        if(!Ford_Bellman())
            return false;
        while(int delta = (++id,FindPath(S,k-mf)))
        {
            mf += delta;
            if(mf == k)
                break;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int x:g[i])
        {
            int l = E[x].ts;
            if(E[x].flow > 0)
                cost += (long long)l;
        }
    }
    return true;
}
int main()
{
    if(fopen("WALK.inp","r"))
    {
        freopen("WALK.inp","r",stdin);
        freopen("WALK.out","w",stdout);
    }
    scanf("%d%d",&n,&m);
    k=2,S=1,T=n;
    for(int i = 1; i <= m; i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        E[i].dau=u;
        E[i].cuoi=v;
        E[i].capa=1;
        E[i].flow=0;
        E[i].ts=w;
        E[i+m].dau=v;
        E[i+m].cuoi=u;
        E[i+m].capa=1;
        E[i+m].flow=0;
        E[i+m].ts=w;
        printf("%d %d %d\n",u,v,w);
    }
/*    for(int i=1; i<=2*m; i++)
    {
        E[4*m+1-i].dau=E[i].cuoi;
        E[4*m+1-i].cuoi=E[i].dau;
        E[4*m+1-i].capa=0;
        E[4*m+1-i].flow=0;
        E[4*m+1-i].ts=-E[i].ts;
    }
    for(int i=1; i<=4*m; i++)
    {
        int u=E[i].dau;
        g[u].push_back(i);
    }
    if(!MinCost()) printf("-1");
    else
    {
        printf("%lld\n",cost);
        for(int i = 1; i <= mf; i++)
        {
            path[1] = S;
            int sl = 1, u = S;
            while(u != T)
            {
                for(int x:g[u])
                {
                    int v= E[x].cuoi, l = E[x].ts;
                    if(E[x].flow == 1)
                    {
                        path[++sl] = v;
                        E[x].flow = 0;
                        u = v;
                        goto L1;
                    }
                }
L1:
                ;
            }
            if(i==1) for(int j = 1; j <= sl; ++j) printf("%d ",path[j]);
            if(i==2) for(int j=sl-1; j>=1; j--) printf("%d ",path[j]);
        }
    } */
}
