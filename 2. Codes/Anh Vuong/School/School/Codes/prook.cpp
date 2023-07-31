#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int a[N][N], d[N], x[N], y[N];
queue <int> q; int n, m;

bool bfs() {
    fill_n(d + 1, n, -1);
    for (int u = 1; u <= n; u++)
        if (!x[u]) {
            q.emplace(u); d[u] = 0;
        }
    bool flag = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= m; v++) {
            if (a[u][v]) continue;
            if (!y[v]) flag = true;
            else if (d[y[v]] < 0) {
                d[y[v]] = d[u] + 1;
                q.emplace(y[v]);
            }
        }
    }
    return flag;
}

bool dfs(int u) {
    for (int v = 1; v <= m; v++) {
        if (a[u][v]) continue;
        if (!y[v] || (d[y[v]] ==
        d[u] + 1 && dfs(y[v]))) {
            x[u] = v; y[v] = u;
            return 1;
        }
    }
    return 0;
}

int matching() {
    int res = 0;
    while (bfs()) {
        for (int u = 1; u <= n; u++)
            if (!x[u]) res += dfs(u);
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            if (c == 'X') a[i][j] = 1;
        }
    cout << matching() << '\n';
    for (int u = 1; u <= n; u++)
        if (x[u]) {
            cout << u << ' ';
            cout << x[u] << '\n';
        }
}