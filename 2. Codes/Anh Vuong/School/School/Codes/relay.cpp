#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

using ll = long long;

struct edge {
    int v; ll w;

    edge(int v, ll w): v(v), w(w) {}

    bool operator < (const edge &o) const {
        return w > o.w;
    }
};

const int N = 100005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll dis[N]; bool spec[N];
vector <edge> adj[N];
priority_queue <edge> pq;
vector <int> vers; int root[N];

void dijkstra() {
    while (pq.size()) {
        edge t = pq.top(); pq.pop();
        if (t.w > dis[t.v]) continue;
        for (const edge &e : adj[t.v])
            if (cmin(dis[e.v], t.w + e.w)) {
                pq.emplace(e.v, dis[e.v]);
                root[e.v] = root[t.v];
            }
    }
}

int main() {
    //freopen("relay.in", "r", stdin);
    //freopen("relay.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    memset(dis, 0x3f, sizeof dis);
    for (int i = 0; i < k; i++) {
        int u; cin >> u; root[u] = u;
        vers.emplace_back(u); spec[u] = 1;
        pq.emplace(u, dis[u] = 0);
    }
    dijkstra();
    ll aa = INF, bb = INF;
    pair <int, int> pp, qq, zz;
    pair <ll, ll> jj, kk;
    jj = kk = {INF, INF};
    for (int u = 1; u <= n; u++) {
        for (edge e : adj[u])
            if (root[u] != root[e.v] &&
            aa > dis[u] + dis[e.v] + e.w) {
                aa = dis[u] + dis[e.v] + e.w;
                pp = {root[u], root[e.v]};
            }
    }
    spec[pp.fi] = spec[pp.se] = 0;
    memset(dis, 0x3f, sizeof dis);
    for (int u : vers)
        if (u != pp.fi && u != pp.se) {
            root[u] = u;
            pq.emplace(u, dis[u] = 0);
        }
    dijkstra();
    for (int u = 1; u <= n; u++)
        for (edge e : adj[u])
            if (root[u] != root[e.v] &&
            bb > dis[u] + dis[e.v] + e.w)
                bb = dis[u] + dis[e.v] + e.w;
    ll res = aa + bb;
    memset(dis, 0x3f, sizeof dis);
    pq.emplace(pp.fi, dis[pp.fi] = 0);
    dijkstra();
    for (int u = 1; u <= n; u++) {
        if (!spec[u]) continue;
        if (jj.fi > dis[u]) {
            jj.se = jj.fi; qq.se = qq.fi;
            jj.fi = dis[u]; qq.fi = u;
        }
        else if (jj.se > dis[u]) {
            jj.se = dis[u]; qq.se = u;
        }
    }
    memset(dis, 0x3f, sizeof dis);
    pq.emplace(pp.se, dis[pp.se] = 0);
    dijkstra();
    for (int u = 1; u <= n; u++) {
        if (!spec[u]) continue;
        if (kk.fi > dis[u]) {
            kk.se = kk.fi; zz.se = zz.fi;
            kk.fi = dis[u]; zz.fi = u;
        }
        else if (kk.se > dis[u]) {
            kk.se = dis[u]; zz.se = u;
        }
    }
    if (qq.fi != zz.fi)
        cmin(res, jj.fi + kk.fi);
    if (qq.fi != zz.se)
        cmin(res, jj.fi + kk.se);
    if (qq.se != zz.fi)
        cmin(res, jj.se + kk.fi);
    if (qq.se != zz.se)
        cmin(res, jj.se + kk.se);
    cout << res << '\n';
}