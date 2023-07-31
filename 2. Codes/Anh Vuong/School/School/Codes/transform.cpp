#include <bits/stdc++.h>
using namespace std;

template <class T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    return u;
}

using ll = long long;

const int N = 205;
const int MOD = 1e9 + 9;

int a[N]; ll dp[N][N], c[N][N];
int n, k, m;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 0; i < N; i++)
        c[i][i] = c[0][i] = 1;
    for (int i = 1; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i][j - 1];
            if (c[i][j] >= MOD) c[i][j] -= MOD;
        }
    while (cin >> n >> k >> m) {
        string s; cin >> s;
        for (int i = 0; i < n; i++)
            a[i] = s[i] - '0';
        cin >> s;
        for (int i = 0; i < n; i++)
            if (s[i] == '1')
                a[i] = 1 - a[i];
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for (int i = 0; i < k; i++)
            for (int x = 0; x <= n; x++) {
                for (int y = 0; y <= n - x; y++) {
                    int on = y, off = m - y;
                    int nw = x + on - off;
                    if (nw >= 0 && nw <= n && off >= 0) {
                        dp[i + 1][nw] += dp[i][x] *
                        c[on][n - x] % MOD * c[off][x] % MOD;
                        dp[i + 1][nw] %= MOD;
                    }
                }
            }
        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += a[i] > 0;
        ll res = dp[k][cnt];
        for (int i = 1; i <= cnt; i++) {
            res = res * i % MOD;
            res = res * inverse(n - cnt + i, MOD) % MOD;
        }
        if (res < 0) res += MOD;
        cout << res << '\n';
    }
}