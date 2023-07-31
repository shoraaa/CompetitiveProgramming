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

template<typename T> bool ckmin(T& a, T b) {
    return a > b ? a = b, 1 : 0;
}
template<typename flow_t, typename cost_t> struct MCMF {
    struct edge { int v; flow_t f, cap; cost_t cost; };
    int N;
    vector<cost_t> dist;
    vector<int> pre;
    vector<bool> inq;
    vector<vector<int>> adj;
    vector<edge> edges;
    explicit MCMF(int N_) : N(N_), dist(N_), pre(N_), adj(N_) {}
    void ae(int u, int v, flow_t cap, cost_t cost) {
        adj[u].push_back((int)edges.size());
        edges.push_back({v, 0, cap, cost});
        adj[v].push_back((int)edges.size());
        edges.push_back({u, 0, 0, -cost});
    }
    bool path(int s, int t) {
        static const cost_t INF = numeric_limits<cost_t>::max() / 2;
        dist.assign(N, INF);
        inq.assign(N, 0);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            inq[v] = 0;
            for(int i : adj[v]) {
                int u = edges[i].v;
                cost_t w = edges[i].cost;
                if(edges[i].f < edges[i].cap && dist[v] + w < dist[u]) {
                    dist[u] = dist[v] + w;
                    pre[u] = i;
                    if(!inq[u]) {
                        q.push(u);
                        inq[u] = 1;
                    }
                }
            }
        }
        return dist[t] != INF;
    }
    pair<flow_t, cost_t> calc(int s, int t) {
        flow_t totflow = 0; cost_t totcost = 0;
        while(path(s, t)) {
            flow_t df = numeric_limits<flow_t>::max();
            for(int i = t; i != s; i = edges[pre[i] ^ 1].v) {
                ckmin(df, edges[pre[i]].cap - edges[pre[i]].f);
            }
            totflow += df;
            totcost += dist[t] * df;
            for(int i = t; i != s; i = edges[pre[i] ^ 1].v) {
                edges[pre[i]].f += df;
                edges[pre[i] ^ 1].f -= df;
            }
        }
        return {totflow, totcost};
    }
};

#define LL long long
const LL INF = 1LL << 60;

#define N 1003

int n, cnt[N];
LL d[N];
vector<pair<int, int>> aj[N];

void dijkstra(int s) {
    for(int i = 0; i < n; ++i) {
        d[i] = INF;
    }
    d[s] = 0;
    vector<int> Q(1, s);
    while(!Q.empty()) {
        auto it = min_element(Q.begin(), Q.end(), [&](int i, int j) {
            return d[i] < d[j];
        });
        swap(*it, Q.back());
        int v = Q.back();
        Q.pop_back();
        for(const auto& [w, u] : aj[v]) {
            if(d[v] + w < d[u]) {
                bool equal_inf = (d[u] == INF);
                d[u] = d[v] + w;
                if(equal_inf) {
                    Q.push_back(u);
                }
            }
        }
    }
}

int main() {
    freopen("DCPP.inp", "r", stdin);
    freopen("DCPP.out", "w", stdout);
    n = rd();
    int m = rd();
    long long res = 0;
    while(m--) {
        int u = rd() - 1, v = rd() - 1, w = rd();
        aj[u].emplace_back(w, v);
        ++cnt[u];
        --cnt[v];
        res += w;
    }
    MCMF<int, long long> f(n + 2);
    for(int i = 0; i < n; ++i) {
        if(cnt[i] < 0) {
            f.ae(n, i, -cnt[i], 0);
            dijkstra(i);
            for(int j = 0; j < n; ++j) {
                if(cnt[j] > 0) {
                    f.ae(i, j, 1e9, d[j]);
                }
            }
        }
        else if(cnt[i] > 0) {
            f.ae(i, n + 1, cnt[i], 0);
        }
    }
    res += f.calc(n, n + 1).second;
    printf("%lld", res);
    return 0;
}

