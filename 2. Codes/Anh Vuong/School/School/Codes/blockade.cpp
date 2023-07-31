#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

using ll = long long;

const int N = 1e5 + 5;

ll ans[N]; int tr[N];
int tim, num[N], low[N], n, m, sz[N];
vector <int> adj[N];

void dfs(int u) {
    low[u] = num[u] = ++tim;
    ll tmp = 0; sz[u] = 1;
    for (int v : adj[u])
        if (!num[v]) {
            tr[v] = u; dfs(v);
            sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
            if (low[v] < num[u])
                tmp += sz[v];
        }
        else if (v != tr[u])
            low[u] = min(low[u], num[v]);
    tmp += n - sz[u];
    for (int v : adj[u])
        if (tr[v] == u &&
            low[v] >= num[u]) {
            ans[u] += tmp * sz[v] * 2;
            tmp += sz[v];
        }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].eb(v); adj[v].eb(u);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        ans[i] += n * 2 - 2;
        cout << ans[i] << '\n';
    }
}
