#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

const int N = 1e5 + 5;
const int LG = 18;

int num[N], low[N];
int p[18][N], tim, dep[N];
vector <int> adj[N];

void dfs(int u) {
    num[u] = low[u] = ++tim;
    for (int v : adj[u])
        if (!num[v]) {
            dep[v] = dep[u] + 1;
            p[0][v] = u; dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (v != p[0][u])
            low[u] = min(low[u], num[v]);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG - 1; ~k; k--)
        if (dep[p[k][u]] >= dep[v])
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
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].eb(v); adj[v].eb(u);
    }
    dfs(1); dep[0] = -1;
    for (int k = 1; k < LG; k++)
        for (int i = 1; i <= n; i++)
            p[k][i] = p[k - 1][p[k - 1][i]];
    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == w || v == w) {
            cout << "NO\n"; continue;
        }
        for (int k = LG - 1; ~k; k--)
            if (dep[p[k][u]] > dep[w])
                u = p[k][u];
        for (int k = LG - 1; ~k; k--)
            if (dep[p[k][v]] > dep[w])
                v = p[k][v];
        if (u == v) {
            cout << "YES\n"; continue;
        }
        if (p[0][u] == w && low[u] >= num[w]) {
            cout << "NO\n"; continue;
        }
        if (p[0][v] == w && low[v] >= num[w]) {
            cout << "NO\n"; continue;
        }
        cout << "YES\n";
    }
}
