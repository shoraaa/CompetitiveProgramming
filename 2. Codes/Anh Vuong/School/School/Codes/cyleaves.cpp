#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int dp[N][2][2][2], tp[2][2][2];
vector <int> adj[N];

int add(int x, int y) {
    if ((x += y) >= MOD) x -= MOD;
    return x;
}

int sub(int x, int y) {
    if ((x -= y) < 0) x += MOD;
    return x;
}

int mul(int x, int y) {
    return (long long)x * y % MOD;
}

void dfs(int u) {
    if (adj[u].empty()) {
        dp[u][0][0][0] = dp[u][1][1][1] = 1;
        return;
    }
    int v = adj[u][0]; dfs(v);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            dp[u][0][i][j] = add(
            dp[v][0][i][j], dp[v][1][i][j]);
            dp[u][1][i][j] = dp[v][0][i][j];
        }
    for (int p = 1; p < int(adj[u].size()); p++) {
        v = adj[u][p]; dfs(v);
        memset(tp, 0, sizeof tp);
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) {
                tp[0][i][j] = add(add(
                mul(dp[u][0][i][0], add(
                dp[v][0][0][j], dp[v][1][0][j])),
                mul(dp[u][0][i][1], add(
                dp[v][0][0][j], dp[v][1][0][j]))),
                mul(dp[u][0][i][0], add(
                dp[v][0][1][j], dp[v][1][1][j])));
                tp[1][i][j] = add(add(
                mul(dp[u][1][i][0], dp[v][0][0][j]),
                mul(dp[u][1][i][1], dp[v][0][0][j])),
                mul(dp[u][1][i][0], dp[v][0][1][j]));
            }
        memcpy(dp[u], tp, sizeof tp);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int p; cin >> p; adj[p].push_back(i);
    }
    dfs(0); int res = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                res = add(res, dp[0][i][j][k]);
    res = sub(res, dp[0][1][1][1]);
    res = sub(res, dp[0][0][1][1]);
    cout << res << '\n';
}