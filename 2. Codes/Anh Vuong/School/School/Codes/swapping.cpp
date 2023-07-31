#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

struct point {
    int x, y;

    point(): x(0), y(0) {}

    point(int x, int y): x(x), y(y) {}
};

using cp = const point&;

point operator + (cp a, cp b) {
    return point(a.x + b.x, a.y + b.y);
}

point operator - (cp a, cp b) {
    return point(a.x - b.x, a.y - b.y);
}

int norm(cp a) {
    return a.x * a.x + a.y * a.y;
}

int sqrdis(cp a, cp b) {
    return norm(a - b);
}

const int N = 505;

int par[N * N], edge[N * N], sz[N * N];
vector <int> adj[N]; bool mark[N * N];
point pt[N]; int n, m, q, d[N * N];

int get_id(int i, int j) {
    return (i - 1) * n + j;
}

int find_set(int u) {
    return u == par[u] ?
    u : find_set(par[u]);
}

int dep(int u) {
    if (~d[u]) return d[u];
    if (par[u] == u) return d[u] = 0;
    return d[u] = dep(par[u]) + 1;
}

void union_set(int u, int v, int e) {
    u = find_set(u);
    v = find_set(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u; edge[v] = e;
    sz[u] += sz[v];
}

int query(int u, int v) {
    int res = INT_MAX;
    while (u != v) {
        if (dep(u) < dep(v)) swap(u, v);
        res = min(res, edge[u]);
        u = par[u];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> pt[i].x >> pt[i].y;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].eb(v); adj[v].eb(u);
    }
    vector <point> cc;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cc.eb(i, j);
    sort(cc.begin(), cc.end(),
    [&](point a, point b) {
        return sqrdis(pt[a.x], pt[a.y])
        > sqrdis(pt[b.x], pt[b.y]);
    });
    iota(par, par + N * N, 0);
    fill(sz, sz + N * N, 1);
    fill(d, d + N * N, -1);
    for (auto p : cc) {
        int e = sqrdis(pt[p.x], pt[p.y]);
        int id = get_id(p.x, p.y);
        for (int v : adj[p.x])
            if (mark[get_id(v, p.y)])
                union_set(id, get_id(v, p.y), e);
        for (int v : adj[p.y])
            if (mark[get_id(p.x, v)])
                union_set(id, get_id(p.x, v), e);
        mark[id] = 1;
    }
    cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        cout << query(get_id(x, y),
        get_id(y, x)) << '\n';
    }
}
