#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

const int N = 1005;

int f[2][N], g[2][N], a[N], b[N];
vector <int> x[N];

void solve() {
    memset(f, 0x3f, sizeof f);
    int n, k; f[0][0] = 0; cin >> n >> k;
    for (int i = 1; i < N; i++) x[i].clear();
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i]; x[b[i]].push_back(a[i]);
    }
    for (int i = 1; i < N; i++) {
        sort(x[i].begin(), x[i].end());
        for (int q = 0; q <= k; q++) {
            g[0][q] = f[0][q]; g[1][q] = f[1][q];
        }
        for (int p = 0; p < int(x[i].size()); p++)
            for (int q = p + 1; q <= k; q++) {
                cmin(g[0][q], f[0][q - p - 1] + 2 * x[i][p]);
                cmin(g[1][q], min(f[0][q - p - 1] + x[i][p],
                f[1][q - p - 1] + 2 * x[i][p]));
            }
        swap(f, g);
    }
    cout << f[1][k] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}