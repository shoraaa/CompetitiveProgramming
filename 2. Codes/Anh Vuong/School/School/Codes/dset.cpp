#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
using ll = long long;

const int N = 2005;
const int mod = 1e9 + 7;
int a[N], lim, d, n; ll dp[N][2], res;
vector <int> adj[N];

void dfs(int u, int p){
    dp[u][0] = dp[u][1] = 0;
    for (int v : adj[u]) if (v != p) dfs(v, u);
    if (a[u] < lim || a[u] > lim + d) return;
    dp[u][a[u] == lim] = 1;
    for (int v : adj[u]) if (v != p){
        dp[u][1] += dp[u][1] * dp[v][0] +
        dp[u][1] * dp[v][1] + dp[u][0] * dp[v][1];
        dp[u][0] += dp[u][0] * dp[v][0];
        dp[u][0] %= mod; dp[u][1] %= mod;
    }
    res = (res + dp[u][1]) % mod;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> d; set <int> s;
    for (int i = 1; i <= n; i++){
        cin >> a[i]; s.insert(a[i]);
    }
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        adj[u].eb(v); adj[v].eb(u);
    }
    for (auto x : s){
        lim = x; dfs(1, 0);
    }
    cout << res << '\n';
}