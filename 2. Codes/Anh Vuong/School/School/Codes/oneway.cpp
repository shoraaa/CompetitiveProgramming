#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define fi first
#define se second

struct edge {
    int u, v;
};

using ii = pair <int, int>;

const int N = 1e5 + 5;
const int LG = 18;

int col[N], bri[N], pred[N];
int num[N], low[N], tim;
int par[N], p[LG][N], d[N];
vector <ii> adj[N]; edge ed[N];

int find_set(int u) {
    return u == par[u] ?
    u : par[u] = find_set(par[u]);
}

void dfs(int u) {
    int v, i;
    num[u] = low[u] = ++tim;
    for (ii pp : adj[u]) {
        tie(v, i) = pp;
        if (v == u) continue;
        if (num[v]) {
            if (p[0][v] == u) bri[v] = 0;
            if (v != p[0][u])
                low[u] = min(low[u], num[v]);
        }
        else {
            d[v] = d[u] + 1; pred[v] = i;
            p[0][v] = u; dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u]) bri[v] = 1;
        }
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int k = LG - 1; ~k; k--)
        if (d[p[k][u]] >= d[v])
            u = p[k][u];
    if (u == v) return u;
    for (int k = LG - 1; ~k; k--)
        if (p[k][u] != p[k][v]) {
            u = p[k][u]; v = p[k][v];
        }
    return p[0][u];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].u >> ed[i].v;
        adj[ed[i].u].eb(ed[i].v, i);
        adj[ed[i].v].eb(ed[i].u, i);
    }
    iota(par + 1, par + n + 1, 1);
    for (int i = 1; i <= n; i++)
        if (!num[i]) dfs(i);
    for (int k = 1; k < LG; k++)
        for (int i = 1; i <= n; i++)
            p[k][i] = p[k - 1][p[k - 1][i]];
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        int r = lca(u, v);
        u = find_set(u);
        while (d[u] > d[r]) {
            if (bri[u]) col[pred[u]] = -1;
            par[u] = p[0][u];
            u = find_set(u);
        }
        v = find_set(v);
        while (d[v] > d[r]) {
            if (bri[v]) col[pred[v]] = 1;
            par[v] = p[0][v];
            v = find_set(v);
        }
    }
    for (int i = 1; i <= n; i++)
        if (bri[i] && ed[pred[i]].v != i)
            col[pred[i]] *= -1;
    for (int i = 0; i < m; i++) {
        if (!col[i]) cout << 'B';
        if (col[i] == 1) cout << 'R';
        if (col[i] == -1) cout << 'L';
    }
}
