#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 105;
const int K = 25;
const ll MOD = 10000000097;
const int B = 57;

map <ll, int> mp;
char s[N][N]; int a[N][N];

int cmp(int x, int y) {
    if (x == 0 && y == 1) return -1;
    if (x == 1 && y == 0) return 1;
    if (x == 1 && y == 2) return -1;
    if (x == 2 && y == 1) return 1;
    if (x == 2 && y == 0) return -1;
    if (x == 0 && y == 2) return 1;
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < k; j++) {
            if (s[i][j] == 'B') a[i][j] = 0;
            if (s[i][j] == 'G') a[i][j] = 1;
            if (s[i][j] == 'K') a[i][j] = 2;
        }
    }
    int mx = 1, x = k / 2, y = k - x;
    for (int i = 0; i < x; i++) mx *= 3;
    for (int ms = 0; ms < mx; ms++) {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            int dif = k, nms = ms;
            for (int j = 0; j < x; j++) {
                dif += cmp(nms % 3, a[i][j]);
                nms /= 3;
            }
            res = (res * B + dif) % MOD;
        }
        mp[res]++;
    }
    mx = 1;
    for (int i = 0; i < y; i++) mx *= 3;
    for (int i = 0; i < n; i++)
        reverse(a[i], a[i] + k);
    long long ans = 0;
    for (int ms = 0; ms < mx; ms++) {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            int dif = k, nms = ms;
            for (int j = 0; j < y; j++) {
                dif -= cmp(nms % 3, a[i][j]);
                nms /= 3;
            }
            res = (res * B + dif) % MOD;
        }
        ans += mp[res];
    }
    cout << ans << '\n';
}