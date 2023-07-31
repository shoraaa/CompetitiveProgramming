#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

#define eb emplace_back

struct edge {
    int u, v, w;
};

const int N = 2505;
const int M = 5005;
const long long inf = 1e18;

edge ed[M]; 
long long d[N]; int p[N]; bool vs[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].u >> ed[i].v;
        cin >> ed[i].w;
    }
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++)
            if (cmin(d[ed[j].v],
            d[ed[j].u] + ed[j].w))
                p[ed[j].v] = ed[j].u;
    int u = -1;
    for (int j = 0; j < m; j++)
        if (cmin(d[ed[j].v],
        d[ed[j].u] + ed[j].w)) {
            p[ed[j].v] = ed[j].u;
            u = ed[j].v; break;
        }
    if (u < 0) {
        cout << "NO\n"; return 0;
    }
    vector <int> path;
    while (!vs[u]) {
        vs[u] = 1; path.eb(u);
        u = p[u];
    }
    cout << "YES\n" << u << ' ';
    while (true) {
        cout << path.back() << ' ';
        if (path.back() == u) break;
        path.pop_back();
    }
}