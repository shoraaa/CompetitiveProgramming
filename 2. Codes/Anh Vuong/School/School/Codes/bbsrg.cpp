#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MOD = 2012;

int dp[N][N]; char s[N];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    dp[0][0] = 1; int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (s[i] == '(') {
            cnt++;
            for (int j = 0; j <= n; j++) {
                if (j)
                    dp[i][j] = dp[i - 1][j - 1];
                if (cnt > j)
                    dp[i][j] += dp[i - 1][j];
                if (dp[i][j] >= MOD)
                    dp[i][j] -= MOD;
            }
        } else {
            cnt--;
            for (int j = 0; j <= n; j++) {
                dp[i][j] = dp[i - 1][j + 1];
                if (cnt >= j)
                    dp[i][j] += dp[i - 1][j];
                if (dp[i][j] >= MOD)
                    dp[i][j] -= MOD;
            }
        }
    if (cnt) cout << "0\n";
    else cout << dp[n][0] << '\n';
}
