#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2005;
const int MOD = 1e9 + 7;

int f[N][N], g[N][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    f[0][0] = 1;
    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++) {
            f[i][j] = ll(f[i - 1][j])
            * j % MOD + f[i - 1][j - 1];
            if (f[i][j] >= MOD) f[i][j] -= MOD;
            g[i][j] = f[i][j] + g[i][j - 1];
            if (g[i][j] >= MOD) g[i][j] -= MOD;
        }
    int q; cin >> q;
    while (q--) {
        int n, m; cin >> m >> n;
        cout << g[n][m] << '\n';
    }
    
}