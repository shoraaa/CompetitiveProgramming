#include <bits/stdc++.h>

using namespace std;

#define eb emplace_back

const int N = 100005, MOD = 1e9 + 7;

int n, dp[2][N];
int par[N], dep[N];
vector <int> adj[N];
bool ban[N], vs[N];
pair <int, int> edges[N];

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

void msub(int &x, int y) {
    if ((x -= y) < 0) x += MOD;
}

void mmul(int &x, int y) {
    x = x * y % MOD;
}

void dfs_span(int u) {
    dep[u] = dep[par[u]] + (vs[u] = 1);
    for (int v : adj[u])
        if (!vs[v]) {
            par[v] = u; dfs_span(v);
        }
}

void dfs_dp(int u, int p) {
    dp[0][u] = 1; vs[u] = 1;
    int ch = 0;
    vector <int> pre, suf, mid;
    pre.eb(1); mid.eb(1);
    for (int v : adj[u])
        if (v != p && !ban[v]) {
            dfs_dp(v, u); ch++;
            pre.eb(dp[1][v]);
            mid.eb(dp[0][v]);
            mmul(dp[0][u], dp[1][v]);
        }
    pre.eb(1); mid.eb(1);
    suf = pre; dp[1][u] = dp[0][u];
    for (int i = 1; i <= ch; i++)
        mmul(pre[i], pre[i - 1]);
    for (int i = ch; i > 0; i--) {
        mmul(suf[i], suf[i + 1]);
        int cur = mid[i];
        mmul(cur, pre[i - 1]);
        mmul(cur, suf[i + 1]);
        madd(dp[1][u], cur);
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u, v; cin >> u >> v;
        edges[i] = {u, v};
        adj[u].eb(v); adj[v].eb(u);
        cerr << u << ' ' << v << '\n';
    }
    dfs_span(1); int x, y;
    for (int i = 1; i <= n; i++) {
        int u, v; tie(u, v) = edges[i];
        if (dep[u] > dep[v]) swap(u, v);
        if (u == par[v]) continue;
        x = u; y = v;
        while (dep[v] >= dep[u]) {
            ban[v] = 1; v = par[v];
        }
    }
    for (int i = 1; i <= n; i++)
        vs[i] = 0;
    int res = 0, add = 1;
    for (int i = 1; i <= n; i++)
        if (!ban[i] && !vs[i]) {
            dfs_dp(i, 0);
            mmul(add, dp[1][i]);
        }
    mmul(add, 2);
    madd(res, add); add = 1;
    for (int i = 1; i <= n; i++) {
        vs[i] = 0;
        ban[i] = i == x || i == y;
    }
    for (int i = 1; i <= n; i++)
        if (!ban[i] && !vs[i]) {
            dfs_dp(i, 0);
            mmul(add, dp[1][i]);
        }
    madd(res, add); add = 1;
    adj[x].erase(find(
    adj[x].begin(), adj[x].end(), y));
    adj[y].erase(find(
    adj[y].begin(), adj[y].end(), x));
    for (int i = 1; i <= n; i++)
        ban[i] = vs[i] = 0;
    for (int i = 1; i <= n; i++)
        if (!ban[i] && !vs[i]) {
            dfs_dp(i, 0);
            mmul(add, dp[1][i]);
        }
    madd(res, add);
    cout << res << '\n';
}