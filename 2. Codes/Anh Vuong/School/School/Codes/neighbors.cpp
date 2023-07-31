#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

const int N = 1e5 + 5;

int sz[N], deg[N], cnt[N], par[N];
vector <int> adj[N], cc[N];

int find_set(int u) {
    return u == par[u] ?
    u : par[u] = find_set(par[u]);
}

void union_set(int u, int v) {
    u = find_set(u); v = find_set(v);
    if (u == v) return;
    if (deg[u] < deg[v]) swap(u, v);
    for (int x : cc[v])
        for (int y : adj[x])
            if (find_set(y) == u) {
                cnt[x]++; cnt[y]++;
            }
    if (sz[u] < sz[v]) swap(u, v);
    for (int x : cc[v]) cc[u].eb(x);
    sz[u] += sz[v]; par[v] = u;
    deg[u] += deg[v];
}

void add_edge(int u, int v) {
    deg[u]++; deg[v]++;
    adj[u].eb(v); adj[v].eb(u);
    if (find_set(u) == find_set(v)) {
        cnt[u]++; cnt[v]++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k, m; cin >> n >> k >> m;
    iota(par, par + N, 0);
    fill(sz, sz + N, 1);
    for (int i = 1; i <= n; i++)
        cc[i].eb(i);
    while (k--) {
        int u, v; cin >> u >> v;
        add_edge(u, v);
    }
    while (m--) {
        int u, v; cin >> u >> v;
        union_set(u, v);
    }
    int q, t, c = 0; cin >> q >> t;
    while (q--) {
        char cmd; cin >> cmd;
        if (cmd == 'T') {
            int u, v; cin >> u >> v;
            u += t * c; v += t * c;
            union_set(u, v);
        }
        if (cmd == 'F') {
            int u, v; cin >> u >> v;
            u += t * c; v += t * c;
            add_edge(u, v);
        }
        if (cmd == '?') {
            int u; cin >> u;
            u += t * c;
            cout << cnt[u] << '\n';
            c = cnt[u];
        }
    }
}