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

const int N = 10005;
const int LG = 14;

int c[N], v[N], lp[N], id[N];
int n, sum, pr, re[N];

int gg(int i, int j) {
    return i * LG + j + n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n; dinic::init(30000);
    int s = 0, t = 30000;
    for (int i = 1; i <= n; i++) {
        cin >> v[i]; sum += v[i]; lp[i] = i;
    }
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 2; i <= n; i++)
        if (lp[i] == i) {
            for (int j = i; j <= n; j += i)
                lp[j] = i;
            id[i] = ++pr; re[pr] = c[i];
        }
    for (int i = 1; i <= n; i++) {
        int x = i;
        dinic::add_edge(s, i, v[i]);
        while (x > 1) {
            int y = lp[x], cnt = 1;
            while (x % y == 0) {
                dinic::add_edge(i,
                gg(id[y], cnt), 1e9);
                cnt++; x /= y;
            }
        }
    }
    for (int i = 1; i <= pr; i++)
        for (int j = 1; j <= LG; j++)
            dinic::add_edge(gg(i, j), t,
            (2 * j - 1) * re[i]);
    cout << sum - dinic::max_flow(s, t);
}