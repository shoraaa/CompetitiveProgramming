#include <bits/stdc++.h>
#define bit(s,i) ((s >> i) & 1)

using namespace std;

int n , m , l[5] , r[5] , cur[5] , nxt[5] , a[50005];
long long f[50005][244];

int main() {
    freopen("repgame.inp","r",stdin);
    freopen("repgame.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i];
    int pw = 1;
    for (int i = 0 ; i < m ; ++i) {
        cin >> l[i] >> r[i];
        pw *= 3;
    }
    memset(f,0x3f,sizeof(f));
    f[0][0] = 0;
    for (int i = 0 ; i < n ; ++i)
    for (int mask = 0 ; mask < pw ; ++mask)
    if (f[i][mask] < 1e15) {
        int x = mask , cnt = 0;
        for (int j = 0 ; j < m ; ++j) {
            cur[j] = x % 3;
            x /= 3;
            if (cur[j] == 2) continue;
            if (cur[j] == 0 && (i + 1 < l[j] || i + 1 > r[j])) continue;
            if (cur[j] == 1 && (i + 1 > r[j])) continue;
            cnt++;
        }
        for (int change = 0 ; change < (1 << cnt) ; ++change) {
            int d = 0;
            for (int j = 0 ; j < m ; ++j) {
                nxt[j] = cur[j];
                if (cur[j] == 2) continue;
                if (cur[j] == 0 && (i + 1 < l[j] || i + 1 > r[j])) continue;
                if (cur[j] == 1 && (i + 1 > r[j])) {
                    nxt[j]++;
                    continue;
                }
                nxt[j] += bit(change , d);
                d++;
            }
            int nwmask = 0;
            int have = m;
            for (int j = m - 1 ; j >= 0 ; --j) {
                if (nxt[j] == 1) have = j;
                nwmask = nwmask * 3 + nxt[j];
            }
            f[i + 1][nwmask] = min(f[i + 1][nwmask] , f[i][mask] + 1ll * a[i + 1] * have);
        }
    }
    long long res = 1e18;
    for (int i = 0 ; i < pw ; ++i) res = min(res , f[n][i]);
    cout << res;
}
