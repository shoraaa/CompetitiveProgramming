#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define popcnt __builtin_popcountll

using ll = long long;

const int N = 105;
const int M = 10005;
const int MOD = 1e9 + 7;

int f[N][M], g[N], n, m;
vector <int> pr[M], adj[N];
    
void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

void msub(int &x, int y) {
    if ((x -= y) < 0) x += MOD;
}

void mmul(int &x, int y) {
    x = ll(x) * y % MOD;
}

void dfs(int u, int p) {
    for (int i = 2; i <= m; i++)
        f[u][i] = 1;
    for (int v : adj[u]) {
        if (v == p) continue; dfs(v, u);
        for (int i = 2; i <= m; i++) {
            int mul = g[i] = 0;
            for (int j = i; j <= m; j += i)
                madd(g[i], f[v][j]);
            int k = pr[i].size();
            for (int b = 1; b < (1 << k); b++) {
                int x = 1, cnt = 0;
                for (int j = 0; j < k; j++)
                    if (b >> j & 1) {
                        x *= pr[i][j]; cnt ^= 1;
                    }
                if (cnt) madd(mul, g[x]);
                else msub(mul, g[x]);
            }
            mmul(f[u][i], mul);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 2; i <= m; i++)
        if (pr[i].empty())
            for (int j = i; j <= m; j += i)
                pr[j].eb(i);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].eb(v); adj[v].eb(u);
    }
    dfs(1, 0); int res = 0;
    for (int i = 2; i <= m; i++)
        madd(res, f[1][i]);
    cout << res << '\n';
}