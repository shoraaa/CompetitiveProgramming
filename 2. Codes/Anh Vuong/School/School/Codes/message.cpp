#include <bits/stdc++.h>
using namespace std;

const int N = 105;

char a[N][N], b[N][N];
int h[N], st[N], l[N];
int tp, n, m, res;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m; res = 0;
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int p = 1 - n; p < n; p++)
            for (int q = 1 - m; q < m; q++) {
                int li = max(0, -p);
                int hi = min(n, n - p);
                int lj = max(0, -q);
                int hj = min(m, m - q);
                if ((hj - lj) * (hi - li) < res) continue;
                for (int j = lj; j < hj; j++) h[j] = 0;
                for (int i = li; i < hi; i++) {
                    st[tp = 0] = lj - 1;
                    for (int j = lj; j < hj; j++) {
                        if (a[i][j] == b[i + p][j + q]) h[j]++;
                        else h[j] = 0;
                        while (tp && h[st[tp]] >= h[j]) tp--;
                        l[j] = st[tp] + 1; st[++tp] = j;
                    }
                    st[tp = 0] = hj;
                    for (int j = hj - 1; j >= lj; j--) {
                        while (tp && h[st[tp]] >= h[j]) tp--;
                        res = max(res, h[j] * (st[tp] - l[j]));
                        st[++tp] = j;
                    }
                }
            }
        cout << res << '\n';
    }
}