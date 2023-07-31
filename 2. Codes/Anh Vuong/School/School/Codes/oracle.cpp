#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1005;
const int inf = 0x3f3f3f3f;

int c[N][N], d[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            cin >> c[i][j + 1];
            c[j + 1][i] = c[i][j + 1];
        }
    ll tot = 0; d[0] = -1;
    for (int i = 1; i <= n; i++)
        d[i] = c[0][i];
    for (int i = 1; i <= n; i++) {
        int u, w = inf;
        for (int i = 1; i <= n; i++)
            if (~d[i] && d[i] < w) {
                w = d[i]; u = i;
            }
        tot += w; d[u] = -1;
        for (int i = 1; i <= n; i++)
            if (~d[i])
                d[i] = min(d[i], c[u][i]);
    }
    cout << tot << '\n';
}