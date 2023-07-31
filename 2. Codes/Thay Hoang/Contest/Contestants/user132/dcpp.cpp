#include<bits/stdc++.h>

using namespace std ;

const int maxN = 1e3 + 10 ;
const long long oo = 1e15 + 10 ;

struct edge {
    int u , v ;
    long long cap , flow , cost ;
    edge () {}
    edge (int _u , int _v , long long _cost , long long _cap) : u(_u) , v(_v) , cost(_cost) , cap(_cap) {
        flow = 0 ;
    }
};

struct minCostFlow {
    vector< vector< int > > g ;
    vector< int > par , inq ;
    vector< long long > d ;
    vector< edge > e ;
    int n , m = 0 , s , t ;

    minCostFlow () {}
    minCostFlow (int _n , int _s , int _t) : n(_n) , s(_s) , t(_t) {
        m = 0 ;
        g.resize(n) ;
        par.resize(n) ; inq.resize(n) ; d.resize(n) ;
    }

    void AddEdge (int u , int v , long long w , long long capacity) {
        e.push_back(edge(u , v , w , capacity)) ;
        e.push_back(edge(v , u , -w , 0)) ;
        g[u].push_back(m) ;
        g[v].push_back(m + 1) ;
        m += 2 ;
    }

    bool bellmanFord () {
        for (int i = 0 ; i < n ; ++ i) {
            par[i] = -1 ;
            d[i] = oo ;
            inq[i] = 0 ;
        }
        queue< int > q ;
        q.push(s) ;
        d[s] = 0 ;
        inq[s] = 1 ; par[s] = s ;
        while (!q.empty()) {
            int u = q.front() ; q.pop() ;
            inq[u] = 0 ;
            for (int i : g[u]) if (e[i].cap > e[i].flow) {
                int v = e[i].v ;
                if (d[v] > d[u] + e[i].cost) {
                    d[v] = d[u] + e[i].cost ;
                    par[v] = i ;
                    if (!inq[v]) {
                        q.push(v) ;
                        inq[v] = 1 ;
                    }
                }
            }
        }
        return par[t] != -1 ;
    }

    long long minCostMaxFlow() {
        long long flow = 0 , cost = 0 ;
        while (bellmanFord()) {
            long long new_flow = oo ;
            for (int v = t ; v != s ;) {
                int i = par[v] ;
                new_flow = min(new_flow , e[i].cap - e[i].flow) ;
                v = e[i].u ;
            }
            for (int v = t ; v != s ;) {
                int i = par[v] ;
                e[i].flow += new_flow ;
                e[i ^ 1].flow -= new_flow ;
                v = e[i].u ;
            }
            cost += d[t] * new_flow ;
            flow += new_flow ;
        }
        return cost ;
    }
};

int n , m ;
int deg[maxN] ;

int main() {
    #define name "dcpp"
    if (fopen(name".inp" , "r")) {
        freopen(name".inp" , "r" , stdin) ;
        freopen(name".out" , "w" , stdout) ;
    }
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;

    cin >> n >> m ;
    minCostFlow G(n + 2 , 0 , n + 1) ;
    long long ans = 0 ;
    for (int i = 1 , u , v , w ; i <= m ; ++ i) {
        cin >> u >> v >> w ;
        deg[u] ++ ;
        deg[v] -- ;
        G.AddEdge(u , v , w , oo) ;
        ans += w ;
    }

//    cout << ans << "\n" ;
    for (int i = 1 ; i <= n ; ++ i) {
        if (deg[i] < 0) G.AddEdge(0 , i , 0 , -deg[i]) ;
        if (deg[i] > 0) G.AddEdge(i , n + 1 , 0 , deg[i]) ;
    }

    cout << ans + G.minCostMaxFlow() << "\n" ;


    return 0 ;
}
