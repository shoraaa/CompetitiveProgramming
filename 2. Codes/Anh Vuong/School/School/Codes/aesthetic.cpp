#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

using ll = long long;

struct edge {
    int u, v; ll w, a;

    edge() {}

    edge(int u, int v, ll w, ll a):
    u(u), v(v), w(w), a(a) {}
};

struct path {
    int v; ll w;

    path() {}

    path(int v, ll w): v(v), w(w) {}

    bool operator < (const path &o) const {
        return w > o.w;
    }
};

using ii = pair <int, int>;

const int N = 300005;
const ll INF = 1e15;

priority_queue <path> pq;
vector <ii> adj[N]; bool brid[N];
ll dis[2][N], lim; edge ed[N];
int n, m, num[N], low[N], tim;

void dijkstra(int s, ll res[]) {
    fill_n(res + 1, n, INF);
    pq.emplace(s, res[s] = 0);
    while (pq.size()) {
        path t = pq.top(); pq.pop();
        if (t.w > res[t.v]) continue;
        for (const ii &e : adj[t.v]) {
            int v, i; tie(v, i) = e;
            if (cmin(res[v], t.w + ed[i].w))
                pq.emplace(v, res[v]);
        }
    }
}

void dfs(int u, int e) {
    num[u] = low[u] = ++tim;
    for (const ii &t : adj[u]) {
        int v, i; tie(v, i) = t;
        if (min(dis[0][u] + dis[1][v],
        dis[1][u] + dis[0][v])
        + ed[i].w >= lim) continue;
        if (i == e) continue;
        if (!num[v]) {
            dfs(v, i);
            cmin(low[u], low[v]);
            brid[i] = low[v] > num[u];
        }
        else cmin(low[u], num[v]);
    }
}

bool check() {
    fill_n(num + 1, n, 0); tim = 0;
    fill_n(brid + 1, m, 0); dfs(1, 0);
    bool flag = 0;
    for (int i = 1; i <= m; i++) {
        if (!brid[i]) continue;
        int u = ed[i].u, v = ed[i].v;
        ll tmp = min(dis[0][u] + dis[1][v],
        dis[1][u] + dis[0][v]) + ed[i].w;
        if (tmp > dis[0][n]) continue;
        if (tmp + ed[i].a >= lim) flag = 1;
    }
    return flag;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        ed[i] = {u, v, w, 0};
    }
    for (int i = m; i > 1; i--) {
        cmax(ed[i - 1].a, ed[i].a);
        cmax(ed[i - 1].a, ed[i].w);
    }
    dijkstra(1, dis[0]);
    dijkstra(n, dis[1]);
    ll lo = dis[0][n], hi = INF;
    while (lo < hi) {
        lim = (lo + hi + 1) / 2;
        if (check()) lo = lim;
        else hi = lim - 1;
    }
    cout << lo << '\n';
}