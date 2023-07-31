#include <bits/stdc++.h>
using namespace std;

namespace dinic {
    #define eb emplace_back

    const int inf = INT_MAX;

    vector <int> head, work, dis;
    vector <int> to, nxt, capa, flow;
    int n, m; queue <int> q;

    void init(int n = 0) {
        dinic::n = n; m = 0;
        head.assign(n + 5, -1);
        work.assign(n + 5, 0);
        dis.assign(n + 5, 0);
        to.clear(); nxt.clear();
        capa.clear(); flow.clear();
    }

    int add_edge(int u, int v, int c, bool r = 0) {
        to.eb(v); nxt.eb(head[u]); flow.eb(0);
        capa.eb(c); head[u] = m++;
        to.eb(u); nxt.eb(head[v]); flow.eb(0);
        capa.eb(c * r); head[v] = m++;
        return m - 2;
    }

    bool bfs(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        dis[s] = 0; q.emplace(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; ~i; i = nxt[i])
                if (dis[to[i]] < 0 && flow[i] < capa[i]) {
                    dis[to[i]] = dis[u] + 1; q.emplace(to[i]);
                }
        }
        return dis[t] >= 0;
    }

    int dfs(int s, int t, int f) {
        if (s == t) return f;
        for (int &i = work[s]; ~i; i = nxt[i])
            if (flow[i] < capa[i] && dis[to[i]] == dis[s] + 1)
                if (int d = dfs(to[i], t, min(f, capa[i] - flow[i]))) {
                    flow[i] += d; flow[i ^ 1] -= d; return d;
                }
        return 0;
    }

    int max_flow(int s, int t) {
        int tot = 0;
        while (bfs(s, t)) {
            copy(head.begin(), head.end(), work.begin());
            while (int aug = dfs(s, t, inf)) tot += aug;
        }
        return tot;
    }
};

const int N = 35;

char a[N][N];
int pts[N], n, src, sink;
string res;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> (a[i] + 1);
    src = 0; sink = n * (n + 1) + 1;
}

int id(int i, int j) {
    return i * n + j;
}

bool cal(int t) {
    dinic::init(sink);
    int mx = 0, val = 0;
    for (int i = 1; i <= n; i++) {
        pts[i] = 0;
        for (int j = 1; j <= n; j++)
            if (a[i][j] == '1') pts[i] += 2;
            else if (a[i][j] == 'd') pts[i]++;
        mx = max(mx, pts[i]);
    }
    for (int i = 1; i <= n; i++)
        if (a[t][i] == '.') pts[t] += 2;
    if (mx > pts[t]) return 0;
    for (int i = 1; i <= n; i++)
        dinic::add_edge(i, sink, pts[t] - pts[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            if (i == t || j == t) continue;
            if (a[i][j] != '.') continue;
            val += 2;
            dinic::add_edge(src, id(i, j), 2);
            dinic::add_edge(id(i, j), i, 2);
            dinic::add_edge(id(i, j), j, 2);
        }
    return dinic::max_flow(src, sink) == val;
}

void process() {
    for (int i = 1; i <= n; i++)
        if (cal(i)) cout << i << ' ';
    cout << '\n';
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        input(); process();
    }
}