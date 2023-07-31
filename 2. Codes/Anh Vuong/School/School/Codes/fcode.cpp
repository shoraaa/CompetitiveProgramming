#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MOD = 1e9 + 7;

long long dp[2][N]; char s[N];

void madd(long long &x, long long y) {
    (x += y) %= MOD;
}

void msub(long long &x, long long y) {
    if (((x -= y) %= MOD) < 0)
        x += MOD;
}

bool open(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool close(char c) {
    return c == ')' || c == ']' || c == '}';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k; dp[1][0] = 1;
    cin >> n >> k >> (s + 1);
    for (int i = 1; i <= n; i++) {
        memset(dp[0], 0, sizeof dp[0]);
        for (int j = 0; j < k; j++) {
            if (open(s[i]))
                madd(dp[0][j + 1], dp[1][j]);
            if (close(s[i]))
                madd(dp[0][j], dp[1][j + 1]);
            if (s[i] == '?') {
                madd(dp[0][j + 1], dp[1][j] * 3);
                madd(dp[0][j], dp[1][j + 1] * 3);
            }
        }
        memset(dp[1], 0, sizeof dp[1]);
        for (int j = 0; j < k; j++) {
            madd(dp[1][j], dp[0][j + 1]);
            madd(dp[1][j + 1], dp[0][j]);
        }
    }
    long long res = dp[1][0];
    memset(dp, 0, sizeof dp);
    dp[1][0] = 1; k--;
    for (int i = 1; i <= n; i++) {
        memset(dp[0], 0, sizeof dp[0]);
        for (int j = 0; j < k; j++) {
            if (open(s[i]))
                madd(dp[0][j + 1], dp[1][j]);
            if (close(s[i]))
                madd(dp[0][j], dp[1][j + 1]);
            if (s[i] == '?') {
                madd(dp[0][j + 1], dp[1][j] * 3);
                madd(dp[0][j], dp[1][j + 1] * 3);
            }
        }
        memset(dp[1], 0, sizeof dp[1]);
        for (int j = 0; j < k; j++) {
            madd(dp[1][j], dp[0][j + 1]);
            madd(dp[1][j + 1], dp[0][j]);
        }
    }
    msub(res, dp[1][0]);
    cout << res << '\n';
}
