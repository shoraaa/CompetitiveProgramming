#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int col[N], n, m, r, b;
vector <int> adj[2][N];
int d[N], dr[N], db[N];
queue <int> q;

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> r >> b;
    for (int i = 1; i <= r; i++) {
        int u; cin >> u; col[u] = 1;
    }
    for (int i = 1; i <= b; i++) {
        int u; cin >> u; col[u] = 2;
    }
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[0][u].push_back(v);
        adj[1][v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        d[i] = dr[i] = db[i] = -1;
    d[1] = 0; q.push(1);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : adj[0][u])
            if (d[v] < 0) {
                d[v] = d[u] + 1;
                q.push(v);
            }
    }
    for (int i = 1; i <= n; i++)
        if (col[i] == 1) {
            dr[i] = 0; q.push(i);
        }
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : adj[1][u])
            if (dr[v] < 0) {
                dr[v] = dr[u] + 1;
                q.push(v);
            }
    }
    if (r == 0)
        for (int i = 1; i <= n; i++)
            dr[i] = 0;
    for (int i = 1; i <= n; i++)
        if (col[i] == 2) {
            db[i] = 0; q.push(i);
        }
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : adj[1][u])
            if (db[v] < 0) {
                db[v] = db[u] + 1;
                q.push(v);
            }
    }
    if (b == 0)
        for (int i = 1; i <= n; i++)
            db[i] = 0;
    int res = n + 1;
    for (int i = 1; i <= n; i++)
        if (~d[i] && ~db[i] && ~dr[i])
            res = min(res, d[i]
            + db[i] + dr[i]);
    if (res == n + 1) cout << "-1\n";
    else cout << res << '\n';
}