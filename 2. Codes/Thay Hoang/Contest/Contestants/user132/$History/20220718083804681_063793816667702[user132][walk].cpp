#include<bits/stdc++.h>

using namespace std ;

const int maxN = 1e5 + 10 ;
const long long loo = 1e18 + 10 ;

int n , m ;

struct edge {
    int u , v , directed = 0 ;
    long long w ;

    int getv (int _u) {
        return u + v - _u ;
    }

    void direct (int _u , int _v) {
        if (u != _u) swap(u , v) ;
        directed = 1 ;
    }
};

edge e[maxN] ;
int inq[maxN] , pre[maxN] , nex[maxN][2] ;
int ban[maxN] ;
long long d[maxN] ;
vector< int > g[maxN] ;

void bellman_ford() {
    memset(inq , 0 , sizeof(inq)) ;
    memset(d , 0x3f , sizeof(d)) ;
    memset(pre , 0 , sizeof(pre)) ;
    d[1] = 0 ; inq[1] = 1 ;
    queue< int > q ;
    q.push(1) ;
    while (!q.empty()) {
        int u = q.front() ; q.pop() ;
        inq[u] = 0 ;

        for (int i : g[u]) if (!e[i].directed || u == e[i].u) {
            int v = e[i].getv(u) ;
            if (d[v] > d[u] + e[i].w) {
                d[v] = d[u] + e[i].w ;
                pre[v] = i ;
                if (!inq[v]) {
                    inq[v] = 1 ;
                    q.push(v) ;
                }
            }
        }
    }
    if (d[n] >= loo) {
        cout << "-1\n" ;
        exit(0) ;
    }
//    cout << d[n] << "\n" ;
}

void show_path (int id , int flag) {
    vector< int > ans ;
    int u = 1 ;
    while (u != n) {
        ans.push_back(u) ;
        int i = nex[u][id] ;
        if (ban[i]) {
            id ^= 1 ;
            i = nex[u][id] ;
        }
        u = e[i].getv(u) ;
    }
    if (flag) reverse(ans.begin() , ans.end()) ;
    for (int i = 0 ; i < int(ans.size()) - 1 ; ++ i) cout << ans[i] << " " ;
    cout << ans.back() ;
    if (!flag) cout << " " ;
}

int main() {
    #define name "abc"
    if (fopen(name".inp" , "r")) {
        freopen(name".inp" , "r" , stdin) ;
        freopen(name".out" , "w" , stdout) ;
    }
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;

    cin >> n >> m ;
    for (int i = 1 ; i <= m ; ++ i) {
        cin >> e[i].u >> e[i].v >> e[i].w ;
        e[i].directed = 0 ;
        g[e[i].u].push_back(i) ;
        g[e[i].v].push_back(i) ;
    }

    bellman_ford() ;
    long long ans = d[n] ;
    int v = n ;
    while (v != 1) {
        int i = pre[v] ;
        int u = e[i].getv(v) ;
        nex[u][0] = i ;
        e[i].direct(v , u) ;
        e[i].w = -e[i].w ;
        v = u ;
    }

    bellman_ford() ;
    ans += d[n] ;
    v = n ;
    while (v != 1) {
        int i = pre[v] ;
        int u = e[i].getv(v) ;
        nex[u][1] = i ;
        if (e[i].directed) ban[i] = 1 ;
        v = u ;
    }

    cout << ans << "\n" ;
    show_path(1 , 0) ;
    cout << n << " " ;
    show_path(0 , 1) ;
//    cout << "\n" ;


    return 0 ;
}
