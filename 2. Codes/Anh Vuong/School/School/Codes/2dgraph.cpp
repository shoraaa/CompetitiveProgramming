#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define eb emplace_back

using ll = long long;

const int N = 50005;

struct path {
    int v; ll w;

    path(int v, ll w): v(v), w(w) {}

    bool operator < (const path &o) const {
        return w > o.w;
    }
};

struct edge {
    int u, v, w, id;

    bool operator < (const edge &o) const {
        return w < o.w;
    }
};

int n[2], m[2]; ll d[N];
vector <path> adj[2][N];
priority_queue <path> pq;
edge ed[N * 2];

struct dsu {
    int par[N], sz[N];

    dsu() {
        iota(par, par + N, 0);
        fill(sz, sz + N, 1);
    }

    int find(int u) {
        return u == par[u] ?
        u : par[u] = find(par[u]);
    }

    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v]; par[v] = u;
        return 1;
    }
} ds[2];

ll dijkstra(int s, int t, vector <path> g[]) {
    memset(d, 0x3f, sizeof d);
    pq.emplace(s, d[s] = 0);
    while (!pq.empty()) {
        path cur = pq.top(); pq.pop();
        if (d[cur.v] != cur.w) continue;
        for (path e : g[cur.v]) {
            if (d[e.v] > cur.w + e.w) {
                d[e.v] = cur.w + e.w;
                pq.emplace(e.v, d[e.v]);
            }
        }
    }
    return d[t];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int type; cin >> type;
    if (type < 2) {
        cin >> n[0] >> m[0];
        for (int i = 0; i < m[0]; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[0][u].eb(v, w);
            adj[0][v].eb(u, w);
        }
        cin >> n[1] >> m[1];
        for (int i = 0; i < m[1]; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[1][u].eb(v, w);
            adj[1][v].eb(u, w);
        }
        cout << dijkstra(1, n[0], adj[0])
        + dijkstra(1, n[1], adj[1]) << '\n';
    }
    else {
        cin >> n[0] >> m[0];
        for (int i = 0; i < m[0]; i++) {
            cin >> ed[i].u >> ed[i].v;
            cin >> ed[i].w; ed[i].id = 0;
        }
        cin >> n[1] >> m[1];
        for (int i = m[0]; i < m[0] + m[1]; i++) {
            cin >> ed[i].u >> ed[i].v;
            cin >> ed[i].w; ed[i].id = 1;
        }
        sort(ed, ed + m[0] + m[1]);
        ll res = 0;
        for (int i = 0; i < m[0] + m[1]; i++)
            if (ed[i].id) {
                if (ds[1].merge(ed[i].u, ed[i].v)) {
                    res += 1ll * n[0] * ed[i].w;
                    n[1]--;
                }
            }
            else {
                if (ds[0].merge(ed[i].u, ed[i].v)) {
                    res += 1ll * n[1] * ed[i].w;
                    n[0]--;
                }
            }
        cout << res << '\n';
    }
}
