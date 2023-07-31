#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 2e5 + 5;

int n, m;
vector<int> adj[N];
int d[N];

void dfs(int u, int pu){
    for (int v : adj[u]) if ( v != pu ){
        dfs(v, u);
        d[u] = max(d[u], d[v] + 1);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    freopen("visit.inp", "r", stdin);
    freopen("visit.out", "w", stdout);

    cin >> n >> m;
    for (int i = 1, u, v; i < n; i ++){
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(0, 0);
    cout << min(n, d[0] + 1 + (m-d[0])/2);

    return 0;
}
