#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

struct edge {
    int u, v, id;

    edge() {}

    edge(int u, int v, int id):
    u(u), v(v), id(id) {}
};

const int N = 10005;

int a[N], b[N];

struct dsu {
    int par[N], sz[N];

    void reset() {
        iota(par, par + N, 0);
        fill(sz, sz + N, 1);
    }

    dsu() {
        reset();
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
} d;

void solve() {
    vector <edge> ed[2], mned, mxed;
    int n, m; cin >> n >> m;
    for (int i = 1; i < n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
        cin >> b[i];
    for (int i = 1; i <= m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        ed[--t].eb(u, v, i);
    }
    d.reset();
    int mn = 0, mx = 0;
    for (edge e : ed[0])
        if (d.merge(e.u, e.v)) {
            mxed.push_back(e);
            mx++;
        }
    d.reset();
    for (edge e : ed[1])
        d.merge(e.u, e.v);
    for (edge e : ed[0])
        if (d.merge(e.u, e.v)) {
            mned.push_back(e);
            mn++;
        }
    int opt = mn, res = INT_MAX;
    for (int i = mn; i <= mx; i++)
        if (res > a[i] + b[n - i - 1]) {
            res = a[i] + b[n - i - 1];
            opt = i;
        }
    d.reset();
    for (edge e : mned)
        if (d.merge(e.u, e.v))
            cout << e.id << ' ';
    for (edge e : mxed)
        if (opt > mn && d.merge(e.u, e.v)) {
            cout << e.id << ' '; opt--;
        }
    for (edge e : ed[1])
        if (d.merge(e.u, e.v))
            cout << e.id << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
