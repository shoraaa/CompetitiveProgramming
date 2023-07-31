#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

bool g[N][N];
queue <int> q; long long a[N];
int d[N], x[N], y[N], n;

bool bfs() {
    for (int u = 1; u <= n; u++)
        if (!x[u]) {
            d[u] = 0; q.emplace(u);
        }
        else d[u] = -1;
    bool flag = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; v++)
            if (g[u][v]) {
                if (!y[v]) flag = 1;
                else if (d[y[v]] < 0) {
                    d[y[v]] = d[u] + 1;
                    q.emplace(y[v]);
                }
            }
    }
    return flag;
}

bool dfs(int u) {
    for (int v = 1; v <= n; v++)
        if (g[u][v])
            if (!y[v] || (d[y[v]] ==
            d[u] + 1 && dfs(y[v]))) {
                x[u] = v; y[v] = u;
                return 1;
            }
    d[u] = -1; return 0;
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
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            long long x = 1ll * a[i] * a[i] + 1ll * a[j] * a[j];
            long long y = sqrt(x);
            if (y * y == x && __gcd(a[i], a[j]) == 1) g[i][j] = 1;
        }
    cout << matching() / 2 << '\n';
}