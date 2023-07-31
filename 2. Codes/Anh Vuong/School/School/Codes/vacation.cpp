#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

using ll = long long;

struct edge {
    int v, w;
    
    edge(int v, int w): v(v), w(w) {}
    
    bool operator < (const edge &o) const {
        return w > o.w;
    }
};

const int N = 52;
const int M = N * N * N;
const ll inf = 1e18;

ll d[3][M][N], h[N], a[3][M];
int n, m; vector <edge> adj[N];

void compute(int s, ll d[M][N]) {
    for (int i = 0; i < M; i++)
        for (int j = 1; j <= n; j++)
            d[i][j] = inf;
    d[0][s] = 0;
    for (int i = 0; i < M - 1; i++)
        for (int j = 1; j <= n; j++) {
            for (edge e : adj[j])
                cmin(d[i + 1][e.v], d[i][j] + e.w);
            cmin(d[i + 1][j], d[i][j] + h[j]);
        }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int p; cin >> p;
    for (int i = 0; i < p; i++) {
        cin >> n >> m;
        for (int u = 1; u <= n; u++) {
            adj[u].clear(); cin >> h[u];
        }
        for (int j = 0; j < m; j++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
        }
        int t; cin >> t;
        compute(1, d[i]);
        for (int j = 0; j < M; j++)
            a[i][j] = d[i][j][t];
    }
    long long res = LLONG_MAX;
    for (int j = 0; j < M; j++) {
        long long cur = 0;
        for (int i = 0; i < p; i++)
            cur += a[i][j];
        cmin(res, cur);
    }
    cout << res << '\n';
}