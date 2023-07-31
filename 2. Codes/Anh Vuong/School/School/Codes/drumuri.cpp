#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

const int N = 2e5 + 5;
vector <int> adj[2][N], g[N];
vector <int> ext, cmp, topo;
int par[N], cnt[N], w[N];
bitset <N> ok, used;

void dfs(int u, bool rev){
    used[u] = true;
    if (rev) cmp.eb(u);
    for (int v : adj[rev][u])
        if (!used[v]) dfs(v, rev);
    if (!rev) ext.eb(u);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[0][u].eb(v);
        adj[1][v].eb(u);
    }
    for (int u = 1; u <= n; u++)
        if (!used[u]) dfs(u, 0);
    used.reset();
    reverse(ext.begin(), ext.end());
    for (int u : ext) if (!used[u]){
        cmp.clear(); dfs(u, 1);
        w[u] = cmp.size();
        for (int v : cmp) par[v] = u;
        topo.eb(u);
    }
    for (int u = 1; u <= n; u++)
        for (int v : adj[1][u])
            if (par[v] != par[u])
                g[par[u]].eb(par[v]);
    int scc = 0;
    for (int u : topo){
        scc++;
        for (int v : g[u])
            scc -= ++cnt[v] == 1;
        if (scc == 1) ok[u] = 1;
    }
    scc = 0;
    for (int u = 1; u <= n; u++){
        g[u].clear(); cnt[u] = 0;
    }
    reverse(topo.begin(), topo.end());
    for (int u = 1; u <= n; u++)
        for (int v : adj[0][u])
            if (par[v] != par[u])
                g[par[u]].eb(par[v]);
    for (int u : topo){
        scc++;
        for (int v : g[u])
            scc -= ++cnt[v] == 1;
        if (scc == 1) ok[u] = ok[u] & 1;
        else ok[u] = 0;
    }
    for (int u = 1; u <= n; u++)
        ok[u] = ok[par[u]];
    cout << ok.count() << '\n';
    for (int u = 1; u <= n; u++)
        if (ok[par[u]]) cout << u << ' ';
}