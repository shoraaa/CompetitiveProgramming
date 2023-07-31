#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int N = 305;

ll dp[N][N];
char inv[256], s[N];

ll cal(int i, int j) {
    if (i > j) return 1;
    if (~dp[i][j]) return dp[i][j];
    dp[i][j] = cal(i + 1, j);
    for (int k = i; k <= j; k++)
        if (s[i] == inv[s[k]]) {
            dp[i][j] += cal(i + 1, k - 1) * cal(k + 1, j);
            dp[i][j] %= MOD;
        }
    return dp[i][j];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    inv[')'] = '(';
    inv[']'] = '[';
    cin >> (s + 1);
    int n = strlen(s + 1);
    memset(dp, -1, sizeof dp);
    cout << cal(1, n) - 1 << '\n';
}
