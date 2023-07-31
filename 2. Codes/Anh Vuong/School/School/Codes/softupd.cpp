#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 1e6 + 5;

struct edge {
    int u, v, w;
};

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
} d;

int spec[N]; edge e[M];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m, k; long long l;
    cin >> n >> m >> l >> k;
    for (int i = 0; i < k; i++) {
        cin >> spec[i];
        d.merge(spec[i], spec[0]);
    }
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v;
        cin >> e[i].w;
    }
    sort(e, e + m,
    [](edge p, edge q) {
        return p.w < q.w;
    });
    long long res = l * (n - k);
    for (int i = 0; i < m; i++)
        if (d.merge(e[i].u, e[i].v))
            res += e[i].w;
    cout << res << '\n';
}