#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 55;
const int K = 5005;

int dp[N][K];

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= i; k++)
                if (j + k * (i - k) <= m)
                    madd(dp[i + 1][j + k * (i - k)], dp[i][j]);
    cout << dp[n][m] << '\n';
}