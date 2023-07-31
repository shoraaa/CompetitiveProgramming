#include <bits/stdc++.h>

using namespace std;

int rd() {
    bool neg = 0; char c = getchar(); for(; c < '0' || c > '9'; c = getchar()) if(c == '-') neg = !neg;
    int n = 0; while('0' <= c && c <= '9') n = (n << 3) + (n << 1) + c - '0', c = getchar();
    return neg ? -n : n;
}
void wr(int n) {
    static char o[11];
    if(n < 0) putchar('-'), n = -n;
    int i = 0; do o[i++] = n % 10 + '0'; while(n /= 10);
    while(i--) putchar(o[i]);
}

template<typename flow_t> struct MF {
    struct edge { int v; flow_t f, cap; };
    static const flow_t inf = numeric_limits<flow_t>::max() / 2;
    int N;
    vector<int> d, ptr;
    vector<vector<int>> adj;
    vector<edge> edges;
    explicit MF(int N_) : N(N_), adj(N_) {}
    void reset() {
        for(edge& e : edges) {
            e.f = 0;
        }
    }
    void ae(int u, int v, flow_t cap) {
        adj[u].push_back((int)edges.size());
        edges.push_back({v, 0, cap});
        adj[v].push_back((int)edges.size());
        edges.push_back({u, 0, 0});
    }
    bool bfs(int s, int t) {
        d.assign(N, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int id : adj[u]) {
                const edge& e = edges[id];
                if(e.f < e.cap && d[e.v] == -1) {
                    d[e.v] = d[u] + 1;
                    if(e.v == t) {
                        return 1;
                    }
                    q.push(e.v);
                }
            }
        }
        return 0;
    }
    flow_t dfs(int u, int t, flow_t f) {
        if(u == t) return f;
        for(int& i = ptr[u]; i < (int)adj[u].size(); ++i) {
            int id = adj[u][i];
            const edge& e = edges[id];
            if(e.f < e.cap && d[e.v] == d[u] + 1) {
                flow_t val = dfs(e.v, t, min(f, e.cap - e.f));
                if(val) {
                    edges[id].f += val;
                    edges[id ^ 1].f -= val;
                    return val;
                }
            }
        }
        return 0;
    }
    flow_t calc(int s, int t) {
        flow_t totflow = 0;
        while(bfs(s, t)) {
            ptr.assign(N, 0);
            while(flow_t df = dfs(s, t, inf))
                totflow += df;
        }
        return totflow;
    }
    int get_match(int v) {
        for(int i : adj[v]) {
            if(edges[i].f > 0) {
                return edges[i].v;
            }
        }
        return -1;
    }
    void partition(int s, vector<bool>& vst) {
        vst.assign(N, 0);
        vst[s] = 1;
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id : adj[v]) {
                if(edges[id].f == edges[id].cap || vst[edges[id].v]) {
                    continue;
                }
                vst[edges[id].v] = 1;
                q.push(edges[id].v);
            }
        }
    }
};
template<typename T> bool ckmin(T& a, T b) {
    return a > b ? a = b, 1 : 0;
}
template<typename flow_t, typename cost_t> struct MCMF {
    struct edge { int v; flow_t f, cap; cost_t cost; };
    int N;
    vector<cost_t> p, dist;
    vector<int> pre;
    vector<vector<int>> adj;
    vector<edge> edges;
    explicit MCMF(int N_) : N(N_), p(N_), dist(N_), pre(N_), adj(N_) {}
    void ae(int u, int v, flow_t cap, cost_t cost) {
        adj[u].push_back((int)edges.size());
        edges.push_back({v, 0, cap, cost});
        adj[v].push_back((int)edges.size());
        edges.push_back({u, 0, 0, -cost});
    }
    bool path(int s, int t) {
        static const cost_t INF = numeric_limits<cost_t>::max() / 2;
        dist.assign(N, INF);
        using dt = pair<cost_t, int>;
        priority_queue<dt, vector<dt>, greater<dt>> q;
        q.push({dist[s] = 0, s});
        while(!q.empty()) {
            dt x = q.top(); q.pop();
            if(x.first != dist[x.second]) continue;
            for(int id : adj[x.second]) {
                const edge& e = edges[id];
                if(e.f < e.cap && ckmin(dist[e.v], x.first + e.cost + p[x.second] - p[e.v])) {
                    pre[e.v] = id;
                    q.push({dist[e.v], e.v});
                }
            }
        }
        return dist[t] != INF;
    }
    pair<flow_t, cost_t> calc(int s, int t) {
        for(int _ = 0; _ < N; ++_) for(int i = 0; i < N; ++i) {
            for(int id : adj[i]) {
                const edge& e = edges[id];
                if(e.cap) ckmin(p[e.v], p[i] + e.cost);
            }
        }
        flow_t totflow = 0; cost_t totcost = 0;
        while(path(s, t)) {
            for(int i = 0; i < N; ++i) p[i] += dist[i];
            flow_t df = numeric_limits<flow_t>::max();
            for(int i = t; i != s; i = edges[pre[i] ^ 1].v) {
                ckmin(df, edges[pre[i]].cap - edges[pre[i]].f);
            }
            totflow += df, totcost += (p[t] - p[s]) * df;
            for(int i = t; i != s; i = edges[pre[i] ^ 1].v) {
                edges[pre[i]].f += df;
                edges[pre[i] ^ 1].f -= df;
            }
        }
        return {totflow, totcost};
    }
};

#define N 2003
struct dt {
    int x, h, p;
    bool operator< (const dt& b) const {
        return x < b.x;
    }
} a[N];

int main() {
    freopen("LIGHT.inp", "r", stdin);
    freopen("LIGHT.out", "w", stdout);
    int n = rd(), t = rd();
    for(int i = 0; i < n; ++i) {
        a[i].x = rd();
        a[i].h = rd();
        a[i].p = rd();
    }
    sort(a, a + n);
    MCMF<int, long long> f(2 * n + 3);
    for(int i = 0; i < n; ++i) {
        if(a[i].x <= a[i].h) {
            f.ae(n << 1, i << 1, 1, 0);
        }
        if(a[i].x + a[i].h >= t) {
            f.ae(i << 1 | 1, n << 1 | 1, 1, 0);
        }
        f.ae(i << 1, i << 1 | 1, 1, a[i].p);
        for(int j = i + 1; j < n; ++j) {
            if(a[i].x + a[i].h >= a[j].x - a[j].h) {
                f.ae(i << 1 | 1, j << 1, 1, 0);
            }
        }
    }
    f.ae(2 * n + 2, n << 1, 2, 0);
    printf("%lld", f.calc(2 * n + 2, n << 1 | 1).second);
    return 0;
}

