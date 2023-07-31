#include <bits/stdc++.h>
#define maxn 10005
#define inf 1e18+1
#define fi first
#define se second
using namespace std;
typedef pair <int,int> II;
int n, m, k, S, T, MFlow, mf, id, cl[maxn], path[maxn];
int dd[maxn], f[maxn][maxn], c[maxn][maxn];
long long d[maxn], cost;
vector <II> g[maxn];

void dungdt()
{
    scanf("%d%d",&n,&m);
    k=2,S=1,T=n;
    int u, v, w;
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back(II(v,w));
        g[v].push_back(II(u,w));
        c[u][v] = c[v][u] = 1;
    }
}

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
        for(II x : g[u])
        {
            int v = x.fi, l = (f[u][v] >= 0)?x.se:-x.se;
            if(f[u][v] < c[u][v] && d[u] + l < d[v])
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
    for(II x:g[u])
    {
        int v = x.fi;
        int l = (f[u][v] >= 0) ? x.se : -x.se;
        if(cl[v] != id && d[v] == d[u] + l)
        {
            if(c[u][v] > f[u][v])
            {
                if(int delta = FindPath(v,min(val,c[u][v] - f[u][v])))
                {
                    f[u][v] += delta;
                    f[v][u] -= delta;
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
        for(II x:g[i])
        {
            int j = x.fi, l = x.se;
            if(f[i][j] > 0)
                cost += (long long)l;
        }
    return true;
}
int main()
{
    dungdt();
    if(!MinCost())
        printf("-1");
    else
    {
        printf("%lld\n",cost);
        for(int i = 1; i <= mf; i++)
        {
            path[1] = S;
            int sl = 1, u = S;
            while(u != T)
            {
                for(II x:g[u])
                {
                    int v= x.fi, l = x.se;
                    if(f[u][v] == 1)
                    {
                        path[++sl] = v;
                        f[u][v] = 0;
                        u = v;
                        goto L1;
                    }
                }
L1:
                ;
            }
            if(i==1)
                for(int j = 1; j <= sl; ++j)
                    printf("%d ",path[j]);
            else for(int j=sl-1; j>=1; j--) printf("%d ",path[j]);
        }
    }
}
