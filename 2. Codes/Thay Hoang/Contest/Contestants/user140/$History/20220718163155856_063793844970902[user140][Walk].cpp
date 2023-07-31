#include <bits/stdc++.h>
#define fi first
#define se second
#define oo 2e14
#define mm 100005
#define pb push_back
#define ff "walk"
using namespace std ;
typedef pair<int,int> pii ;
typedef int64_t ll ;
typedef vector<int> vi ;

int n,m,k ;
ll d[mm] ;
ll p[mm] ;
int tr[mm] ;
vi ke[mm] ;

struct edge
{
    int u,v,c,f,w ;
} e[mm*4] ;

struct dl
{
    ll w ;
    int u ;
    bool operator < (const dl&tg) const
    {
        return (w > tg.w) ;
    }
};
priority_queue<dl> s ;

void read()
{
    cin >> n >> m ;
    int sl = 0 ;
    while (m--)
    {
        int u,v,w ;
        cin >> u >> v >> w ;
        e[sl++] = {u,v,1,0,w} ;
        e[sl++] = {v,u,0,0,-w} ;
        e[sl++] = {v,u,1,0,w} ;
        e[sl++] = {u,v,0,0,-w} ;
    }
    m = sl ;
    for (int i=0 ; i<m ; ++i)
    {
        ke[e[i].u].pb(i) ;
    }
    memset(p,0,sizeof(p)) ;
}

void dj()
{
    fill(d+1,d+1+n,oo) ;
    d[1] = 0 ;
    s.push({0,1}) ;
    while (s.size())
    {
        int u = s.top().u ;
        s.pop() ;
        for (auto i : ke[u])
        {
            int v = e[i].v ;
            if (e[i].f == e[i].c) continue ;
            ll tg = (ll) e[i].w + p[e[i].u] - p[e[i].v] ;
            if (d[v] > d[u] + tg)
            {
                d[v] = d[u] + tg ;
                tr[v] = i ;
                s.push({d[v],v}) ;
            }
        }
    }
    for (int i=1 ; i<=n ; ++i) p[i] += d[i] ;
}

int tangluong()
{
    int u = n ;
    while (u != 1)
    {
        int i = tr[u] ;
        e[i].f++ ;
        e[i^1].f-- ;
        u = e[i].u ;
    }
}

void truyvet(vi &ve,ll &sum)
{
    ve.clear() ;
    sum = 0 ;
    ve.pb(1) ;
    int u = 1 ;
    while (1)
    {
        for (auto i : ke[u])
        {
            if (e[i].f == 1)
            {
                sum = (ll) sum + e[i].w ;
                e[i].f = 0 ;
                u = e[i].v ;
                break ;
            }
        }
        ve.pb(u) ;
        if (u == n) break ;
    }
}

void solve()
{
    for (int buoc=1 ; buoc<=2 ; ++buoc)
    {
        dj() ;
        if (d[n] == oo)
        {
            cout << -1 ;
            return ;
        }
        tangluong() ;
    }
    vi dg1 ;
    vi dg2 ;
    ll tg1 ;
    ll tg2 ;
    truyvet(dg1,tg1) ;
    truyvet(dg2,tg2) ;
    dg1.pop_back() ;
    reverse(dg2.begin(),dg2.end()) ;
    cout << tg1 + tg2 << "\n" ;
    for (auto i : dg1) cout << i << " " ;
    for (auto i : dg2) cout << i << " " ;
}

int main()
{
    freopen(ff".inp","r",stdin) ;
    freopen(ff".out","w",stdout) ;
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;

    read() ;

    solve() ;

    return 0 ;
}
