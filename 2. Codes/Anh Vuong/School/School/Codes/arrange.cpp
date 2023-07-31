#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

const int N = 2005;
const int INF = 0x3f3f3f3f;

int a[N], b[N], c[N];
int dp[N][N], s[N];

int len(int i, int j) {
    return s[j] - s[i] + j - i - 1;
}

void solve() {
    int m, n; cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            dp[i][j] = INF;
    for (int i = 1; i <= n; i++)
        if (len(0, i) <= m) dp[i][0] = 0;
    s[n + 1] = INF;
    for (int i = 1; i < n; i++) {
        int k = i;
        for (int j = 1; j <= n; j++)
            a[j] = b[j] = INF;
        for (int j = i - 1; ~j; j--) {
            if (len(j, i) > m) break;
            while (len(j, i) > len(i, k)) k++;
            cmin(a[k - 1], dp[i][j] + len(j, i));
            cmin(b[k], dp[i][j] - len(j, i));
        }
        int mdp = INF;
        for (int j = i + 1; j <= n; j++) {
            if (len(i, j) > m) break;
            cmin(mdp, b[j]);
            cmin(dp[j][i], mdp + len(i, j)); 
        }
        mdp = INF;
        for (int j = n; j > i; j--) {
            cmin(mdp, a[j]);
            if (len(i, j) > m) continue;
            cmin(dp[j][i], mdp - len(i, j));
        }
    }
    int res = INF;
    for (int j = n - 1; ~j; j--)
        cmin(res, dp[n][j]);
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}