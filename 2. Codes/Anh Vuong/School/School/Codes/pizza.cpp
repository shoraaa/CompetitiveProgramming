#include <bits/stdc++.h>

using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

using ll = long long;

struct edge {
    int v, w, i;
    
    edge(int v, int w, int i): v(v), w(w), i(i) {}
};

struct path {
    int v; ll w;
    
    path(int v, ll w): v(v), w(w) {}
    
    bool operator < (const path &o) const {
        return w > o.w;
    }
};

const int N = 1e5 + 5;
const int M = 2e5 + 5;

ll disS[N], disT[N]; bool mark[M];
vector <edge> adj[N], rev[N];
priority_queue <path> pq;
tuple <int, int, int> edges[M];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v, w, i);
        rev[v].emplace_back(u, w, i);
        edges[i] = {u, v, w};
    }
    memset(disS, 0x3f, sizeof disS);
    pq.emplace(1, disS[1] = 0);
    while (pq.size()) {
        path t = pq.top(); pq.pop();
        if (disS[t.v] < t.w) continue;
        for (edge e : adj[t.v])
            if (cmin(disS[e.v], t.w + e.w))
                pq.emplace(e.v, disS[e.v]);
    }
    ll maxDis = -1, disST = disS[2];
    set <int> maxPos;
    memset(disT, 0x3f, sizeof disT);
    pq.emplace(2, disT[2] = 0);
    while (pq.size()) {
        path t = pq.top(); pq.pop();
        if (disT[t.v] < t.w) continue;
        int cntShort = 0;
        for (edge e : rev[t.v]) {
            if (cmin(disT[e.v], t.w + e.w))
                pq.emplace(e.v, disT[e.v]);
            if (disS[e.v] + t.w + e.w == disST)
                cntShort++;
        }
        if (disT[t.v] < maxDis || cntShort > 1 ||
        (disT[t.v] == maxDis && maxPos.size() > 1))
            for (edge e : rev[t.v])
                mark[e.i] = 1;
        for (edge e : rev[t.v])
            if (disS[e.v] + t.w + e.w == disST) {
                if (t.w + e.w > maxDis) {
                    maxDis = t.w + e.w;
                    maxPos.clear();
                    maxPos.insert(e.v);
                }
                else if (t.w + e.w == maxDis)
                    maxPos.insert(e.v);
            }
    }
    for (int i = 0; i < m; i++, cout << '\n') {
        int u, v, w; tie(u, v, w) = edges[i];
        if (disS[u] + disT[v] + w == disST)
            cout << (mark[i] ? "SOSO" : "SAD");
        else if (disS[v] + disT[u] + w < disST)
            cout << "HAPPY"; else cout << "SOSO";
    }
}