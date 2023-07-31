#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

const int N = 3e5 + 5;

struct edge {int u, v, w;} ed[N];
int par[N], dep[N], dsu[N], ped[N];
vector <pair <int, int>> adj[N];
bitset <N> mst;

int find_set(int u) {
    return u == dsu[u] ?
    u : dsu[u] = find_set(dsu[u]);
}

void dfs(int u) {
    for (auto e : adj[u]) {
        int v, i; tie(v, i) = e;
        if (v != par[u]) {
            par[v] = u; ped[v] = i;
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> ed[i].u >> ed[i].v;
    for (int i = 1; i < n; i++) {
        int j; cin >> j; mst[j] = 1;
        adj[ed[j].u].eb(ed[j].v, j);
        adj[ed[j].v].eb(ed[j].u, j);
    }
    dfs(1); int col = 0;
    for (int i = 1; i <= n; i++)
        dsu[i] = i;
    for (int i = 1; i <= m; i++) {
        int x = find_set(ed[i].u);
        int y = find_set(ed[i].v);
        vector <int> gg;
        while (x != y) {
            if (dep[x] < dep[y])
                swap(x, y);
            gg.eb(ped[x]);
            dsu[x] = par[x];
            x = find_set(x);
        }
        sort(gg.begin(), gg.end());
        for (int e : gg)
            ed[e].w = ++col;
        if (!mst[i])
            ed[i].w = ++col;
    }
    for (int i = 1; i <= m; i++)
        cout << ed[i].w << ' ';
}