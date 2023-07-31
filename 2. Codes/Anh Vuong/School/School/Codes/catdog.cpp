#include <bits/stdc++.h>
using namespace std;

namespace hopcroft_karp {
    vector <vector <int>> g;
    vector <int> x, y, d;
    int n, m; queue <int> q;

    void init(int n = 0, int m = 0) {
        hopcroft_karp::n = n;
        hopcroft_karp::m = m;
        g.assign(n + 5, vector <int> ());
        x.assign(n + 5, 0);
        y.assign(m + 5, 0);
        d.assign(n + 5, 0);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    bool bfs() {
        for (int u = 1; u <= n; u++)
            if (!x[u]) {
                d[u] = 0; q.emplace(u);
            }
            else d[u] = -1;
        bool flag = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int v : g[u])
                if (!y[v]) flag = true;
                else if (d[y[v]] < 0) {
                    d[y[v]] = d[u] + 1;
                    q.emplace(y[v]);
                }
        }
        return flag;
    }

    bool dfs(int u) {
        for (int v : g[u])
            if (!y[v] || (d[y[v]] ==
            d[u] + 1 && dfs(y[v]))) {
                x[u] = v; y[v] = u;
                return true;
            }
        d[u] = -1; return false;
    }

    int max_matching() {
        int tot = 0;
        while (bfs())
            for (int u = 1; u <= n; u++)
                if (!x[u]) tot += dfs(u);
        return tot;
    }
};

void solve() {
    int c, d, n; cin >> c >> d >> n;
    vector <pair <int, int>> cat, dog;
    for (int i = 1; i <= n; i++) {
        char x, y; int p, q;
        cin >> x >> p >> y >> q;
        if (x == 'C')
            cat.emplace_back(p, q);
        else dog.emplace_back(p, q);
    }
    hopcroft_karp::init(cat.size(), dog.size());
    for (int i = 0; i < cat.size(); i++)
        for (int j = 0; j < dog.size(); j++)
            if (cat[i].first == dog[j].second
            || cat[i].second == dog[j].first)
                hopcroft_karp::add_edge(i + 1, j + 1);
    cout << n - hopcroft_karp::max_matching() << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}