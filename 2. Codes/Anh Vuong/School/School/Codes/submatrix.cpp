#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int n, m, p, a[N][N], cnt[N * N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    int res = 1;
    for (int d = 1 - n; d < m; d++) {
        memset(cnt, 0, sizeof cnt);
        int len = 0, cur = 0;
        for (int i = max(1 - d, 1);
        i <= min(n, m - d); i++) {
            int j = i + d;
            for (int x = i - len; x <= i; x++)
                cur += ++cnt[a[x][j]] == 1;
            for (int y = j - len; y < j; y++)
                cur += ++cnt[a[i][y]] == 1;
            while (cur > p) {
                for (int x = i - len; x <= i; x++)
                    cur -= --cnt[a[x][j - len]] == 0;
                for (int y = j - len + 1; y <= j; y++)
                    cur -= --cnt[a[i - len][y]] == 0;
                len--;
            }
            res = max(res, ++len);
        }
    }
    cout << res << '\n';
}