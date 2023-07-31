#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

namespace dinic {
    const int inf = INT_MAX;
 
    vector <int> head, dis, work;
    vector <int> to, nxt, capa, flow;
    int n; queue <int> q;
 
    void init(int n) {
        dinic::n = n;
        head.assign(n + 5, -1);
        dis.assign(n + 5, 0);
        work.assign(n + 5, 0);
        to.clear(); nxt.clear();
        capa.clear(); flow.clear();
    }
 
    void add_edge(int u, int v, int c, bool r = 0) {
        to.push_back(v); nxt.push_back(head[u]);
        capa.push_back(c); flow.push_back(0);
        head[u] = to.size() - 1;
        to.push_back(u); nxt.push_back(head[v]);
        capa.push_back(c * r); flow.push_back(0);
        head[v] = to.size() - 1;
    }
 
    bool bfs(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        dis[s] = 0; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i >= 0; i = nxt[i])
                if (flow[i] < capa[i] && dis[to[i]] < 0) {
                    dis[to[i]] = dis[u] + 1; q.push(to[i]);
                }
        }
        return dis[t] >= 0;
    }
 
    int dfs(int s, int t, int f) {
        if (s == t) return f;
        for (int &i = work[s]; i >= 0; i = nxt[i])
            if (flow[i] < capa[i] && dis[to[i]] == dis[s] + 1) {
                int d = dfs(to[i], t, min(f, capa[i] - flow[i]));
                if (d > 0) {
                    flow[i] += d; flow[i ^ 1] -= d; return d;
                }
            }
        return 0;
    }
 
    int max_flow(int s, int t) {
        int res = 0, aug;
        while (bfs(s, t)) {
            copy(head.begin(), head.end(), work.begin());
            while ((aug = dfs(s, t, inf)) > 0) res += aug;
        }
        return res;
    }
};

const int N = 55;

vector <int> tr[2][N];
int n, sum = 0, res = 0, c[N];

void dfs(int u, int p, int id) {
    if (p) dinic::add_edge(u, p, sum + 1);
    for (int v : tr[id][u])
        if (v != p) dfs(v, u, id);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n; int s = 0, t = n + 1;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tr[0][u].push_back(v);
        tr[0][v].push_back(u);
    }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tr[1][u].push_back(v);
        tr[1][v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        if (c[i] > 0) sum += c[i];
    }
    for (int i = 1; i <= n; i++) {
        dinic::init(n + 1);
        for (int u = 1; u <= n; u++)
            if (c[u] > 0)
                dinic::add_edge(s, u, c[u]);
            else dinic::add_edge(u, t, -c[u]);
        dfs(i, 0, 0); dfs(i, 0, 1);
        int cur = dinic::max_flow(s, t);
        cmax(res, sum - cur);
    }
    cout << res << '\n';
}