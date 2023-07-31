#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

using ll = long long;

struct edge {
    int v; ll w;
    
    edge(int v, ll w): v(v), w(w) {}
    
    bool operator <
    (const edge &o) const {
        return w > o.w;
    }
};

const int N = 5005;

set <ll> dis[N];
priority_queue <edge> pq;
vector <edge> adj[N];
int n, m, k;

void dijkstra(int s) {
    dis[1].insert(0); pq.emplace(s, 0);
    while (pq.size()) {
        edge cur = pq.top(); pq.pop();
        if (dis[cur.v].size() == k) continue;
            dis[cur.v].insert(cur.w);
        for (edge e : adj[cur.v])
            pq.emplace(e.v, cur.w + e.w);
    }
}

void solve() {
     cin >> n >> m;
     for (int i = 1; i <= n; i++) {
        dis[i].clear(); adj[i].clear();
    }
     for (int i = 1; i <= m; i++) {
         int u, v, w;
         cin >> u >> v >> w;
         adj[u].eb(v, w);
     }
     cin >> k; dijkstra(1);
     if (dis[n].size() < k) cout << "-1\n";
     else cout << *dis[n].rbegin() << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}