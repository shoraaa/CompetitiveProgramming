#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

struct node {
    int x = 0, y = 0;

    node(int x = 0, int y = 0):
    x(x), y(y) {}
};

struct edge {
    node v; int w;

    edge(node v, int w): v(v), w(w) {}
};

const int N = 55;

int a[N][N], d[N][N];
vector <edge> g[N][N];
node x[N][N], y[N][N];
queue <node> q; int n, m;
int lo, hi, mi;

void bfs(int x, int y) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            d[i][j] = -1;
    q.emplace(x, y); d[x][y] = 0;
    while (q.size()) {
        node t = q.front(); q.pop();
        int w = d[t.x][t.y];
        if (a[t.x][t.y] == 3)
            g[x][y].eb(t, w);
        if (t.x > 1)
            if (d[t.x - 1][t.y] < 0
                && a[t.x - 1][t.y]) {
                d[t.x - 1][t.y] = w + 1;
                q.emplace(t.x - 1, t.y);
            }
        if (t.y > 1)
            if (d[t.x][t.y - 1] < 0
                && a[t.x][t.y - 1]) {
                d[t.x][t.y - 1] = w + 1;
                q.emplace(t.x, t.y - 1);
            }
        if (t.x < n)
            if (d[t.x + 1][t.y] < 0
                && a[t.x + 1][t.y]) {
                d[t.x + 1][t.y] = w + 1;
                q.emplace(t.x + 1, t.y);
            }
        if (t.y < m)
            if (d[t.x][t.y + 1] < 0
                && a[t.x][t.y + 1]) {
                d[t.x][t.y + 1] = w + 1;
                q.emplace(t.x, t.y + 1);
            }
    }
}

bool bfs() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (!x[i][j].x) {
                d[i][j] = 0;
                q.emplace(i, j);
            }
            else d[i][j] = -1;
        }
    bool flag = false;
    while (q.size()) {
        node u = q.front(); q.pop();
        int w = d[u.x][u.y];
        for (edge e : g[u.x][u.y]) {
            if (e.w > mi) continue;
            node v = y[e.v.x][e.v.y];
            if (!v.x) flag = true;
            else if (d[v.x][v.y] < 0) {
                d[v.x][v.y] = w + 1;
                q.push(v);
            }
        }
    }
    return flag;
}

bool dfs(node u) {
    for (edge e : g[u.x][u.y]) {
        if (e.w > mi) continue;
        node v = y[e.v.x][e.v.y];
        if (!v.x || (d[v.x][v.y] ==
        d[u.x][u.y] + 1 && dfs(v))) {
            x[u.x][u.y] = e.v;
            y[e.v.x][e.v.y] = u;
            return true;
        }
    }
    return false;
}

int matching() {
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            x[i][j] = y[i][j] = 0;
    while (bfs()) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!x[i][j].x)
                    res += dfs({i, j});
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m; int car = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            if (c == '.') a[i][j] = 1;
            if (c == 'C') {
                a[i][j] = 2; car++;
            }
            if (c == 'P') a[i][j] = 3;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == 2) bfs(i, j);
    lo = 0; hi = n * m;
    while (lo < hi) {
        mi = (lo + hi) / 2;
        if (matching() == car) hi = mi;
        else lo = mi + 1;
    }
    mi = hi;
    if (matching() < car){
        cout << "-1\n"; return 0;
    }
    cout << mi << '\n';
}