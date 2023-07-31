#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define ctz __builtin_ctzll

const int N = 2e5 + 5;
int dep[N], anc[19][N], sz[N], n, q;
vector <int> adj[N];

void dfs_init(int u, int p){
    sz[u] = 1;
    for (int v : adj[u])
        if (v != p){
            dep[v] = dep[u] + 1;
            dfs_init(v, u); anc[0][v] = u;
            sz[u] += sz[v];
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
    if (k > dep[u]) return -1;
    while (k > 0){
        u = anc[ctz(k)][u]; k -= k & -k;
    }
    return u;
}

void query(int u, int v){
    if (u == v){
        cout << 0 << ' ' << n << ' ' << 0 << '\n';
    }
    else {
        int r = lca(u, v); bool flag = 0;
        int dis = dep[u] + dep[v] - 2 * dep[r];
        if (dep[u] < dep[v]){
            swap(u, v); flag = true;
        }
        int le = 0, gr = 0, eq = 0;
        if (dep[u] == dep[v]){
            int x = kth_anc(u, dep[v] - dep[r] - 1);
            int y = kth_anc(v, dep[v] - dep[r] - 1);
            le = sz[x]; gr = sz[y]; eq = n - le - gr;
        }
        else {
            int x = kth_anc(u, (dis - 1) / 2);
            le = sz[x];
            if (dis % 2 == 0) eq = sz[anc[0][x]] - sz[x];
            gr = n - le - eq;
        }
        if (flag) swap(le, gr);
        cout << le << ' ' << eq << ' ' << gr << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cin >> n;
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    dfs_init(1, 0); dep[0] = -1; cin >> q;
    for (int k = 1; k <= 18; k++)
        for (int u = 1; u <= n; u++)
            if (dep[u] >= (1 << k))
                anc[k][u] = anc[k - 1][anc[k - 1][u]];
    for (int i = 1, u, v; i <= q; i++){
        cin >> u >> v; query(u, v);
    }