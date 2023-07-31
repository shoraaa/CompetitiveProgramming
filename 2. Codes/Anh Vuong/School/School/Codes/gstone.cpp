    #include <bits/stdc++.h>
    using namespace std;

    template <class X, class Y>
    bool cmin(X &a, const Y &b) {
        return a > b ? a = b, 1 : 0;
    }

    using ll = long long;

    struct node {
        int u, t; ll w;

        bool operator < (const node &o) const {
            return w > o.w;
        }
    };

    const int N = 305;
    const ll INF = 1e12;

    vector <int> adj[N], rev[N];
    vector <int> road[N];
    ll dis[N][N]; int mat[N];
    priority_queue <node> pq;

    void solve() {
        int n, m, s, r;
        cin >> n >> m >> s >> r;
        for (int i = 1; i <= n; i++)
            road[i].clear();
        for (int i = 1; i <= r; i++)
            adj[i].clear();
        for (int i = 1; i <= s; i++)
            rev[i].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= s; j++)
                dis[i][j] = INF;
        for (int i = 1; i <= m; i++) {
            int u, v; cin >> u >> v;
            road[u].push_back(v);
            road[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) {
            int c; cin >> c;
            while (c--) {
                int t; cin >> t;
                dis[i][t] = 0;
                pq.push({i, t, 0});
            }
        }
        for (int i = 1; i <= r; i++) {
            int c; cin >> c;
            while (c--) {
                int t; cin >> t;
                adj[i].push_back(t);
                rev[t].push_back(i);
            }
            cin >> mat[i];
        }
        while (pq.size()) {
            node p = pq.top(); pq.pop();
            if (p.w > dis[p.u][p.t]) continue;
            for (int v : road[p.u])
                if (cmin(dis[v][p.t], p.w + 1))
                    pq.push({v, p.t, p.w + 1});
            for (int i : rev[p.t]) {
                ll cur = 0;
                for (int t : adj[i])
                    cur += dis[p.u][t];
                if (cmin(dis[p.u][mat[i]], cur))
                    pq.push({p.u, mat[i], cur});
            }
        }
        ll res = INF;
        for (int i = 1; i <= n; i++)
            cmin(res, dis[i][1]);
        if (res == INF) cout << "-1\n";
        else cout << res << '\n';
    }

    int main() {
        cin.tie(0)->sync_with_stdio(0);
        int t; cin >> t;
        while (t--) solve();
    }