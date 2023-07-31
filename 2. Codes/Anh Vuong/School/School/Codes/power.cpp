#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int dp[N], res = 0; bool led[N];
vector <int> adj[N];

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u); dp[u] += dp[v];
        res = max(res, dp[v] + led[u]);
    }
    if (led[u]) {
        dp[u]--; dp[u] = max(dp[u], 1);
    }
    res = max(res, dp[u]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    string s; cin >> s;
    for (int i = 1; i <= n; i++)
        led[i] = s[i - 1] - '0';
    dfs(1, 0); cout << res << '\n';
}