#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 3005;
const int MOD = 1e9 + 7;

ll dp[N][N][2]; char s[N];

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

void madd(ll &x, ll y) {
    if ((x += y) >= MOD) x -= MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k, p;
    cin >> n >> k >> p;
    dp[0][0][k == 0] = 1;
    if (p < 2) {
        cin >> (s + 1);
        int d = 0, ok = 0; ll res = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= k; j++) {
                if (j) {
                    madd(dp[i][j - 1][0], dp[i - 1][j][0]);
                    madd(dp[i][j - 1][1], dp[i - 1][j][1]);
                }
                if (j < k) {
                    if (j + 1 < k)
                        madd(dp[i][j + 1][0], dp[i - 1][j][0]);
                    else madd(dp[i][k][1], dp[i - 1][j][0]);
                    madd(dp[i][j + 1][1], dp[i - 1][j][1]);
                }
            }
        for (int i = 1; i <= n; i++)
            if (s[i] == ')') {
                madd(res, dp[n - i][d + 1][1]);
                if (ok)
                    madd(res, dp[n - i][d + 1][0]);
                d--;
            }
            else ok |= ++d == k;
        cout << res << '\n';
    }
    else {
        ll m, tmp; cin >> m;
        int d = 0, ok = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j) {
                    dp[i][j - 1][0] += dp[i - 1][j][0];
                    dp[i][j - 1][1] += dp[i - 1][j][1];
                }
                if (j < k) {
                    if (j + 1 < k)
                        dp[i][j + 1][0] += dp[i - 1][j][0];
                    else dp[i][k][1] += dp[i - 1][j][0];
                    dp[i][j + 1][1] += dp[i - 1][j][1];
                }
            }
            for (int j = 0; j <= k; j++) {
               cmin(dp[i][j][0], m);
               cmin(dp[i][j][1], m);
            }
        }
        if (m > dp[n][0][1]) {
            cout << "-1\n"; return 0;
        }
        for (int i = 1; i <= n; i++) {
            tmp = dp[n - i][d + 1][1];
            if (ok) tmp += dp[n - i][d + 1][0];
            if (d < k && tmp >= m) {
                cout << '('; ok |= ++d == k;
            }
            else {
                cout << ')'; m -= tmp; d--;
            }
        }
        cout << '\n';
    }
}