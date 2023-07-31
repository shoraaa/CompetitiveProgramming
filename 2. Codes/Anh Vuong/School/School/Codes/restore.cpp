#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

#define eb emplace_back

struct edge {
    int u, v, w;
    
    edge(int u, int v, int w):
    u(u), v(v), w(w) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector <int> d(n + 1, 1e9);
    vector <edge> ed; d[0] = 0;
    for (int i = 1; i <= n; i++) {
        ed.eb(i - 1, i, 1);
        ed.eb(i, i - 1, 0);
    }
    for (int i = 0; i < m; i++) {
        int l, r, k, v;
        cin >> l >> r >> k >> v;
        if (!v) ed.eb(r + 1, l, -k);
        else ed.eb(l, r + 1, k - 1);
    }
    for (int i = 0; i < n; i++)
        for (edge e : ed)
            cmin(d[e.v], d[e.u] + e.w);
    for (edge e : ed)
        if (cmin(d[e.v], d[e.u] + e.w)) {
            cout << "-1\n"; return 0;
        }
    for (int i = 1; i <= n; i++)
        cout << 1 - d[i] + d[i - 1] << ' ';
}