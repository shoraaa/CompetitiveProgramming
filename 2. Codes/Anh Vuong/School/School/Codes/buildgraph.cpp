#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector <int> strong[N], weak[N], cmp;
bitset <N> in_st, used[2];
bool cycle;

void dfs1(int u){
    used[0][u] = 1; cmp.push_back(u);
    for (int v : weak[u])
        if (!used[0][v]) dfs1(v);
}

void dfs2(int u){
    if (cycle) return;
    used[1][u] = 1; in_st[u] = 1;
    for (int v : strong[u]){
        if (in_st[v]){
            cycle = true; break;
        }
        if (!used[1][v]) dfs2(v);
    }
    in_st[u] = 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, res = 0; cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        strong[u].push_back(v);
        weak[u].push_back(v);
        weak[v].push_back(u);
    }
    for (int u = 1; u <= n; u++)
        if (!used[0][u]){
            cmp.clear(); dfs1(u);
            cycle = 0;
            for (int v : cmp)
                if (!used[1][v]) dfs2(v);
            if (cycle) res += cmp.size();
            else res += cmp.size() - 1; 
        }
    cout << res << '\n';
}