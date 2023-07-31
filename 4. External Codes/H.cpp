#include<bits/stdc++.h>
#define ll long long
#define pi pair<ll, ll>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
const ll oo = 1e18;

int n, m, k;
vector<int> adj[N];
vector<pi> ad[N];
ll d[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    if ( fopen("trash.inp", "r") ){
        freopen("trash.inp", "r", stdin);
        freopen("trash.out", "w", stdout);
    }

    cin >> n >> m;
    for (int i = 1; i <= m; i ++){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    cin >> k;
    for (int i = 1; i <= k; i ++){
        int u, v, t;
        cin >> t >> u >> v;
        ad[u].pb({v, t});
        ad[v].pb({u, t});
    }

    priority_queue<pi, vector<pi>, greater<pi>> heap;
    for (int i = 1; i <= n; i ++) d[i] = oo;
    d[1] = 0; heap.push({d[1], 1});
    while ( heap.size() ){
        int u = heap.top().se;
        ll du = heap.top().fi;
        heap.pop();

//        cout << u << ' ' << du << '\n';

        if ( du != d[u] ) continue;

        for (int v : adj[u]) if ( d[v] > d[u] + 1 ){
            d[v] = d[u] + 1;
            heap.push({d[v], v});
        }

        for (auto it : ad[u]){
            int v = it.fi;
            ll t = it.se;
            ll w = max(1ll, t-d[u]);
            if ( d[v] > d[u] + w ){
                d[v] = d[u] + w;
                heap.push({d[v], v});
            }
        }
    }

    cout << ( d[n] == oo ? -1 : d[n] );

    return 0;
}
