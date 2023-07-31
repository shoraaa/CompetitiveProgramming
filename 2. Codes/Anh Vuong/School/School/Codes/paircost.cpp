#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define eb emplace_back

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    if (a == -1) return a = b, 1;
    return a > b ? a = b, 1 : 0;
}

using ll = long long;

const int N = 305;
const int M = 1005;
const ll inf = LLONG_MAX;
const ll MOD = 1e9;

vector <int> g[N];
int d[N][N]; queue <int> q;
struct edge {int u, v; ll w;} ed[M];
ll ans[N][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].u >> ed[i].v >> ed[i].w;
        g[ed[i].u].eb(ed[i].v);
        g[ed[i].v].eb(ed[i].u);
    }
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            ans[i][j] = inf;
    memset(d, -1, sizeof d);
    for (int i = 1; i <= n; i++) {
        d[i][i] = 0; q.emplace(i);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int v : g[u])
                if (d[i][v] < 0) {
                    d[i][v] = d[i][u] + 1;
                    q.emplace(v);
                }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int u = 1; u < n; u++)
            for (int v = u + 1; v <= n; v++) {
                if (d[ed[i].u][u] >= 0
                && d[ed[i].v][v] >= 0)
                    ans[u][v] = min(ans[u][v],
                    ed[i].w * (d[ed[i].u][u]
                    + d[ed[i].v][v] + 1));
                if (d[ed[i].u][v] >= 0
                && d[ed[i].v][u] >= 0)
                    ans[u][v] = min(ans[u][v],
                    ed[i].w * (d[ed[i].u][v]
                    + d[ed[i].v][u] + 1));
            }
    }
    ll res = 0; bool big = 0;
    for (int u = 1; u < n; u++)
        for (int v = u + 1; v <= n; v++)
            if (ans[u][v] < inf &&
            (res += ans[u][v]) >= MOD) {
                big = 1; res %= MOD;
            }
    if (big) cout << setw(9) << setfill('0') << res;
    else cout << res;
}