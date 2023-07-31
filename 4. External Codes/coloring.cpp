#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

ll dp[N], pw[N]; bool vs[N];
vector <int> adj[N];
int par[N], dif[N], dep[N];
int n, k, res = 1, cnt, len;

int madd(int x, int y) {
    if ((x += y) >= MOD) x -= y;
    return x;
}

int msub(int x, int y) {
    if ((x -= y) < 0) x += MOD;
    return x;
}

int mmul(int x, int y) {
    return ll(x) * y % MOD;
}

void dfs(int u) {
    vs[u] = 1; cnt++;
    for (int v : adj[u])
        if (!vs[v]) {
            dep[v] = dep[u] + 1; dfs(v);
        }
        else if (dep[v] < dep[u] - 1)
            len = dep[u] - dep[v] + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> dif[i];
    for (int i = 1; i <= n; i++) {
        adj[i].push_back(dif[i]);
        if (dif[dif[i]] != i)
            adj[dif[i]].push_back(i);
    }
    pw[0] = 1; dp[0] = 0;
    pw[1] = k - 1; dp[1] = k;
    pw[2] = mmul(k - 1, k - 1);
    dp[2] = mmul(k, k - 1);
    for (int i = 3; i <= n; i++) {
        dp[i] = msub(mmul(k,
        pw[i - 1]), dp[i - 1]);
        pw[i] = mmul(pw[i - 1], k - 1);
    }
    for (int i = 1; i <= n; i++) {
        if (vs[i]) continue;
        cnt = 0; len = -1; dfs(i);
        if (len > 0) {
            res = mmul(res, dp[len]);
            res = mmul(res, pw[cnt - len]);
        }
        else {
            res = mmul(res, k);
            res = mmul(res, pw[cnt - 1]);
        }
    }
    cout << res << '\n';
}