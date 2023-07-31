#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define eb emplace_back
#define all(v) (v).begin(), (v).end()

const int N = 2e5 + 5;
vector <int> adj[N];
ll w[N], par[N], dp[N], c[N]; int n;
ll sum[N], res = LLONG_MAX, cost = 0;

void dfs_init(int u, int p){
    for (int v : adj[u]) if (v != p){
        dfs_init(v, u); dp[u] += dp[v];
        c[u] += c[v]; sum[u] += sum[v];
    }
    dp[u] += sum[u]; c[u]++; sum[u] += w[u] * c[u];
}

void dfs_sol(int u, int p, ll x, ll y){
    res = min(res, x);
    for (int v : adj[u]) if (v != p)
        dfs_sol(v, u, x - sum[v] * 2 + y + sum[u] - w[u] * c[u] + w[u] * (n - c[v]),
                y + sum[u] - w[u] * c[u] + 1ll * w[u] * (n - c[v]) - sum[v]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; cin >> w[i++]);
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v; u++; v++;
        adj[u].eb(v); adj[v].eb(u);
    }
    dfs_init(1, 0); dfs_sol(1, 0, dp[1], 0);
    cout << res << '\n';
}