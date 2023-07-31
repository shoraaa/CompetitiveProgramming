#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1005;
const int MOD = 1e9 + 7;
const char *open = "({[";
const char *close = ")}]";

char s[N]; int dp[2][60000][11];

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int main() {
    int n, k;
    cin >> n >> k >> (s + 1);
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bool c = i & 1; int mx = 1;
        memset(dp[c], 0, sizeof dp[c]);
        for (int l = 0; l < k; l++) {
            for (int j = 0; j < mx; j++) {
                for (int t = 0; t < 3; t++) {
                    if (s[i] == '?' || s[i] == open[t])
                        madd(dp[c][j * 3 + t][l + 1], dp[!c][j][l]);
                    if (s[i] == '?' || s[i] == close[t])
                        madd(dp[c][j][l], dp[!c][j * 3 + t][l + 1]);
                }
            }
            mx *= 3;
        }
    }
    int res = dp[n & 1][0][0]; k--;
    memset(dp[0], 0, sizeof dp[0]);
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bool c = i & 1; int mx = 1;
        memset(dp[c], 0, sizeof dp[c]);
        for (int l = 0; l < k; l++) {
            for (int j = 0; j < mx; j++) {
                for (int t = 0; t < 3; t++) {
                    if (s[i] == '?' || s[i] == open[t])
                        madd(dp[c][j * 3 + t][l + 1], dp[!c][j][l]);
                    if (s[i] == '?' || s[i] == close[t])
                        madd(dp[c][j][l], dp[!c][j * 3 + t][l + 1]);
                }
            }
            mx *= 3;
        }
    }
    res -= dp[n & 1][0][0];
    if (res < 0) res += MOD;
    cout << res << '\n';
}
