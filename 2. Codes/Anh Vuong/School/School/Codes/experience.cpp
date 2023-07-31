#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 5;
const ll INF = 1e18;

ll dp[N][3]; int w[N];
vector <int> adj[N];

void dfs(int u) {
    ll sum = 0;
    for (int v : adj[u]) {
        dfs(v);
        sum += dp[v][2];
    }
    dp[u][0] = sum - w[u];
    dp[u][1] = sum + w[u];
    for (int v : adj[u]) {
        dp[u][0] = max(dp[u][0],
        dp[v][0] + sum - dp[v][2]);
        dp[u][1] = max(dp[u][1],
        dp[v][1] + sum - dp[v][2]);
    }
    dp[u][2] = max(dp[u][0] + w[u],
    dp[u][1] - w[u]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    dfs(1); cout << dp[1][2];
}
