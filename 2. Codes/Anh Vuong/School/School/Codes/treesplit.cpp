#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;
const int mod = 1e9 + 7;
int col[N]; ll dp[N][2];
vector <int> adj[N];

void dfs(int u, int p){
    dp[u][col[u]] = 1;
    for (int v : adj[u]) if (v != p){
        dfs(v, u);
        dp[u][1] = dp[u][1] * dp[v][1] +
        dp[u][1] * dp[v][0] + dp[u][0] * dp[v][1];
        dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]);
        dp[u][1] %= mod; dp[u][0] %= mod;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; cin >> col[i++]);
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v; u++; v++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0); cout << dp[1][1] << '\n';
}