#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, a, b; double w;
};

const int N = 1e5 + 5;

edge ed[N];
int par[N], sz[N];

int find_set(int u) {
    return u == par[u] ?
    u : par[u] = find_set(par[u]);
}

bool union_set(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u == v) return 0;
    if (sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v]; par[v] = u;
    return 1;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].u >> ed[i].v;
        cin >> ed[i].a >> ed[i].b;
    }
    double lo = 0.0, hi = 205.0, ans;
    int ansa, ansb;
    for (int st = 0; st < 20; st++) {
        double mi = (lo + hi) / 2;
        for (int i = 1; i <= n; i++) {
            par[i] = i; sz[i] = 1;
        }
        for (int i = 0; i < m; i++)
            ed[i].w = double(ed[i].a) - mi * ed[i].b;
        sort(ed, ed + m,
        [](edge p, edge q) {
            return p.w > q.w;
        });
        int sa = 0, sb = 0; double tot = 0;
        for (int i = 0; i < m; i++)
            if (union_set(ed[i].u, ed[i].v)) {
                sa += ed[i].a;
                sb += ed[i].b;
                tot += ed[i].w;
            }
        if (tot >= 0) {
            lo = ans = mi;
            ansa = sa; ansb = sb;
        }
        else hi = mi;
    }
    int t = __gcd(ansa, ansb);
    ansa /= t; ansb /= t;
    cout << ansa << '/' << ansb << '\n';
}
