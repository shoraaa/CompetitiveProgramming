#include <bits/stdc++.h>
    
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

using ll = long long;

const int N = 705;

ll dp[N][N], a[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n - 2; i > 0; i--)
        for (int j = i + 2; j <= n; j++)
            for (int k = i + 1; k < j; k++)
                cmax(dp[i][j], dp[i][k] +
                dp[k][j] + (a[i] + a[j]) * a[k]);
    cout << dp[1][n] << '\n';
}