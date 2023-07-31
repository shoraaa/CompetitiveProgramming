#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MOD = 1e9 + 7;

long long dp[N][N]; char s[N];

void madd(long long &x, long long y) {
    (x += y) %= MOD;
}

bool open(char c) {
    return c == '(' || c == '[' || c == '{';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k >> (s + 1);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (open(s[i]))
                madd(dp[i][j + 1], dp[i - 1][j]);
            else {
                madd(dp[i][j], dp[i - 1][j + 1]);
                madd(dp[i][j + 1], dp[i - 1][j] * 3);
            }
        }
    }
    long long res = dp[n][0];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1; k--;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (open(s[i]))
                madd(dp[i][j + 1], dp[i - 1][j]);
            else {
                madd(dp[i][j], dp[i - 1][j + 1]);
                madd(dp[i][j + 1], dp[i - 1][j] * 3);
            }
        }
    }
    res = (res - dp[n][0] + MOD) % MOD;
    cout << res << '\n';
}
