#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

const int N = 505;
const int K = 35;

int dp[N][N];

void init() {
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) {
            if (i + j == 0) continue;
            for (int x = N - 1; x >= i; x--)
                for (int y = N - 1; y >= j; y--)
                    cmax(dp[x][y], dp[x - i][y - j] + 1);
        }
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            if (x) cmax(dp[x][y], dp[x - 1][y]);
            if (y) cmax(dp[x][y], dp[x][y - 1]);
        }
}

void query() {
    int n, m; cin >> n >> m;
    cout << dp[n][m] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init(); int t; cin >> t;
    while (t--) query();
}