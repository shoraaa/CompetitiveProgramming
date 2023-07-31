#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector <int> adj[N];
vector <int> ext, cmp, rev[N];
int par[N];
bitset <N> need, used;

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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    used.reset();
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++)
        need[i] = 1;
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!used[i]) dfs1(i);
    used.reset(); int scc = 0;
    reverse(ext.begin(), ext.end());
    for (int u : ext) if (!used[u]){
        cmp.clear(); dfs2(u); scc++;
        for (int v : cmp){
            par[v] = u;
            if (v != u) need[v] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j : adj[i])
            if (par[i] != par[j])
                need[par[j]] = 0;
    cout << need.count() << '\n';
}