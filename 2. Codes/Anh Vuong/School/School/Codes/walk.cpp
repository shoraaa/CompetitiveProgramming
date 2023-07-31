#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;
vector <int> adj[N];
vector <int> ext, cmp, rev[N];
int par[N]; ll w[N], c[N], dp[N];
bitset <N> used;

void dfs1(int u){
    used[u] = true;
    for (int v : adj[u])
        if (!used[v]) dfs1(v);
    ext.push_back(u);
}

void dfs2(int u){
    used[u] = true;
    cmp.push_back(u);
    for (int v : rev[u])
        if (!used[v]) dfs2(v);
}

ll dfs3(int u){
    if (dp[u] != -1) return dp[u];
    dp[u] = w[u];
    for (int v : rev[u])
        dp[u] = max(dp[u], dfs3(v) + w[u]);
    return dp[u];
}

int main(){
    memset(dp, -1, sizeof dp);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; cin >> c[i++]);
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!used[i]) dfs1(i);
    used.reset();
    reverse(ext.begin(), ext.end());
    for (int u : ext) if (!used[u]){
        cmp.clear(); dfs2(u);
        for (int v : cmp){
            par[v] = u; w[u] += c[v];
        }
    }
    for (int i = 1; i <= n; i++)
        rev[i].clear();
    for (int i = 1; i <= n; i++)
        for (int j : adj[i])
            if (par[i] != par[j])
                rev[par[i]].push_back(par[j]);
    for (int i = 1; i <= n; i++)
        cout << dfs3(par[i]) << ' ';
}