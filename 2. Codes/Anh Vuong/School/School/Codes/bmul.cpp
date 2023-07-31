#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

int dp[2][500005][2][2], a[51], p[500005][20];

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n = 0;
    ll m, u, b; cin >> m >> u >> b;
    if (m <= 500000){
        while (u > 0){
            a[++n] = u % b; u /= b;
        }
        reverse(a + 1, a + n + 1);
        dp[0][0][1][0] = 1;
        for (int j = 0; j < m; j++)
            for (int d = 0; d < b; d++)
                p[j][d] = (j * b + d) % m;
        for (int i = 1; i <= n; i++) {
            bool c = i & 1;
            memset(dp[c], 0, sizeof dp[c]);
            for (int j = 0; j < m; j++) {
                for (int d = 0; d < b; d++)
                    madd(dp[c][p[j][d]][0][d > 0],
                    dp[!c][j][0][0]);
                for (int d = 1; d < b; d++)
                    madd(dp[c][p[j][d]][0][1],
                    dp[!c][j][0][1]);
                for (int d = 0; d <= a[i]; d++)
                    madd(dp[c][p[j][d]][d == a[i]][d > 0],
                    dp[!c][j][1][0]);
                for (int d = 1; d <= a[i]; d++)
                    madd(dp[c][p[j][d]][d == a[i]][1],
                    dp[!c][j][1][1]);
            }
        }
        cout << (dp[n & 1][0][0][1] +
        dp[n & 1][0][1][1]) % MOD << '\n';
    }
    else {
        int res = u / m;
        for (int i = 1; m * i <= u; ++i){
            ll x = m * i;
            while (x > 0){
                if (x % b == 0){res--; break;} x /= b;
            }
        }
        cout << res << '\n';
    }
}