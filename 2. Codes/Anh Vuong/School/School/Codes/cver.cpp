#include <bits/stdc++.h>
using namespace std;

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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; string s;
    cin >> n >> m >> s;
    dinic::init(n + 1); s = " " + s;
    for (int i = 1; i <= n; i++)
        if (s[i] == 'R')
            dinic::add_edge(0, i, INT_MAX);
        else if (s[i] == 'B')
            dinic::add_edge(i, n + 1, INT_MAX);
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        if (s[u] == s[v] && s[u] != '?')
            continue;
        dinic::add_edge(u, v, 1, 1);
    }
    cout << dinic::max_flow(0, n + 1) << '\n';
}