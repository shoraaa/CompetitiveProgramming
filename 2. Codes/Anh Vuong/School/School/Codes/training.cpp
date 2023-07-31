#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

const int N = 51;
const int INF = 0x3f3f3f3f;

int dp[N][N][N]; bool cal[N][N];
int c[N], a[N], t[N][N], k, n;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, 0xc0, sizeof dp);
    cin >> k >> n;
    for (int i = 1; i <= k; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            cin >> t[i][j];
    for (int i = 1; i <= n; i++)
        dp[i][i][a[i]] = 0;
    for (int i = n - 1; i > 0; i--)
        for (int j = i + 1; j <= n; j++)
                for (int m = i; m < j; m++) {
                    for (int x = 1; x <= k; x++)
                        for (int y = 1; y <= k; y++) {
                            int w = dp[i][m][x] + dp[m + 1][j][y];
                            cmax(dp[i][j][x], w + c[y]);
                            cmax(dp[i][j][y], w + c[x]);
                            cmax(dp[i][j][t[x][y]], w);
                            cmax(dp[i][j][t[y][x]], w);
                        }
                }
    int res = 0;
    for (int i = 1; i <= k; i++)
        cmax(res, dp[1][n][i] + max(c[i], 0));
    cout << res << '\n';
}