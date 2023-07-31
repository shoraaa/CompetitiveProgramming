#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define ctz __builtin_ctz
using ll = long long;

struct edge{
    int v, w, id;

    edge(){}

    edge(int v, int w, int id): v(v), w(w), id(id){}
};

const int N = 2e5 + 5;
int anc[19][N], par[N], dep[N], n, q;
ll len[19][N], dis[N];
vector <edge> adj[N];

void dfs(int u, int p){
    for (auto e : adj[u])
        if (e.v != p){
            dep[e.v] = dep[u] + 1;
            dis[e.v] = dis[u] + e.w;
            par[e.v] = e.id; anc[0][e.v] = u;
            len[0][e.v] = e.w; dfs(e.v, u);
        }
}

void prepare(){
    dfs(1, 0); dep[0] = -1;
    for (int k = 1; k <= 18; k++)
        for (int u = 1; u <= n; u++)
            if (dep[u] >= (1 << k)){
                anc[k][u] = anc[k - 1][anc[k - 1][u]];
                len[k][u] = len[k - 1][u] +
                            len[k - 1][anc[k - 1][u]];
            }
}

int lca(int u, int v){
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 18; ~k; k--)
        if (dep[anc[k][u]] >= dep[v])
            u = anc[k][u];
    if (u == v) return u;
    for (int k = 18; ~k; k--)
        if (anc[k][u] != anc[k][v]){
            u = anc[k][u]; v = anc[k][v];
        }
    return anc[0][u];
}

int kth_anc(int u, int k){
    while (k > 0){
        u = anc[ctz(k)][u]; k -= k & -k;
    }
    return u;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cin >> n;
    for (int i = 1, u, v, w; i < n; i++){
        cin >> u >> v >> w;
        adj[u].eb(v, w, i); adj[v].eb(u, w, i);
    }
    prepare(); cin >> q;
    for (int i = 1, u, v, r; i <= q; i++){
        ll t; cin >> u >> v >> t; r = lca(u, v);
        if (t >= dis[u] + dis[v] - 2 * dis[r]){
            cout << "-1\n"; continue;
        }
        if (t < dis[u] - dis[r]){
            for (int k = 18; ~k; k--)
                if (anc[k][u] && len[k][u] <= t){
                    t -= len[k][u]; u = anc[k][u];
                }
            cout << par[u] << '\n';
        }
        else {
            t = dis[u] + dis[v] - 2 * dis[r] - t;
            for (int k = 18; ~k; k--)
                if (anc[k][v] && len[k][v] < t){
                    t -= len[k][v]; v = anc[k][v];
                }
            cout << par[v] << '\n';
        }
    }
}