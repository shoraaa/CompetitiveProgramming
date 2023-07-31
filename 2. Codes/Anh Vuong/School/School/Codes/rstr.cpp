#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int f[N][N], g[N];
bool ok[N][N]; char s[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m >> (s + 1);
    if (m == 1) return cout << 0, 0;
    memset(f, 0xc0, sizeof f);
    for (int i = 1; i <= n; i++) f[i][i] = 1;
    for (int i = n - 1; i > 0; i--)
        for (int j = i + 1; j <= n; j++) {
            for (int k = i + 1; k <= j; k++) {
                if (s[i] == s[k])
                    f[i][j] = max(f[i][j],
                    f[i][k - 1] + f[k][j]);
                if (ok[k][j])
                    f[i][j] = max(f[i][j], f[i][k - 1]);
                ok[i][j] |= ok[i][k - 1] && ok[k][j];
            }
            if (f[i][j] >= m) ok[i][j] = 1;
        }
    for (int i = 1; i <= n; i++) {
        g[i] = g[i - 1] + 1;
        for (int j = 1; j <= i; j++)
            if (ok[j][i])
                g[i] = min(g[i], g[j - 1]);
    }
    cout << g[n] << '\n';
}