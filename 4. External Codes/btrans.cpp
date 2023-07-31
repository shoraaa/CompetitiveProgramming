#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000 + 10;
const int INF = (int)(1e9);
string a, b;
int p_0[MAXN], p_1[MAXN];
int f[MAXN][MAXN];
int n, x, y, z, t;
int cost(char u, char v) {
    if (u == v) return 0;
    if (u == '0') return x;
    if (u == '1') return y;
    if (u == '?') return z;
}
void solve() {
    cin >> n >> x >> y >> z >> t;
    cin >> a; cin >> b;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) f[i][j] = INF;
    }
    f[0][0] = 0;
    int cnt_0 = 0, cnt_1 = 0;
    for(int i = 1; i <= n; i++) {
        if (b[i - 1] == '0') cnt_0++, p_0[cnt_0] = i;
        else cnt_1++, p_1[cnt_1] = i;
        for(int j = 0; j <= i; j++) {
            // j = number of 0(s) so far.
            if (j > 0) {
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + cost(a[i - 1], '0') + t * ((j <= cnt_0) ? (i - p_0[j]) : 0));
            }
            f[i][j] = min(f[i][j], f[i - 1][j] + cost(a[i - 1], '1') + t * ((i - j <= cnt_1) ? (i - p_1[i - j]) : 0));
        }
    }
    //if (f[n][cnt_0] == INF) f[n][cnt_0] = -1;
    cout << f[n][cnt_0] << endl;
}
int main()
{
    freopen("btrans.in", "r", stdin);
    freopen("btrans.out", "w", stdout);
    int test;
    cin >> test;
    while (test --) {
        solve();
    }
}
