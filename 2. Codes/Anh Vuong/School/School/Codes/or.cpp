#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
using ll = long long;
const int N = 2005;
ll a[2005]; int dp[N];
bool f[105][105], er[N][N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, x, y; cin >> n >> x >> y;
    for (int i = 1; i <= n; i++){
        cin >> a[i]; a[i] += a[i - 1];
    }
    ll res = (1ll << 42) - 1;
    if (x > 1){
        for (int p = 41; ~p; p--){
            memset(f, 0, sizeof f); f[0][0] = 1;
            for (int i = 1; i <= n; i++)
                for (int j = i; j > 0; j--){
                    ll tmp = a[i] - a[j - 1];
                    if (((tmp >> p & 1) == 0) && !er[i][j])
                        for (int k = 1; k <= y; k++)
                            f[i][k] |= f[j - 1][k - 1];
                }
            bool flag = false;
            for (int i = x; i <= y; i++) flag |= f[n][i];
            if (flag){
                for (int i = 1; i <= n; i++)
                    for (int j = i; j > 0; j--){
                        ll tmp = a[i] - a[j - 1];
                        if (tmp >> p & 1) er[i][j] = 1;
                    }
                res -= 1ll << p;
            }
        }
    }
    else {
        for (int p = 41; ~p; p--){
            memset(dp, 0x3f, sizeof dp); dp[0] = 0;
            for (int i = 1; i <= n; i++)
                for (int j = i; j > 0; j--){
                    ll tmp = a[i] - a[j - 1];
                    if (((tmp >> p & 1) == 0) && !er[i][j])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            if (dp[n] <= y){
                for (int i = 1; i <= n; i++)
                    for (int j = i; j > 0; j--){
                        ll tmp = a[i] - a[j - 1];
                        if (tmp >> p & 1) er[i][j] = 1;
                    }
                res -= 1ll << p;
            }
        }
    }
    cout << res << '\n';
}
