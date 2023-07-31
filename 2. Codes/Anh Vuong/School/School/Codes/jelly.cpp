#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

const int N = 2005;
const int X = 10005;

struct item {int u, v;} a[N];

int f[N][X], g[N][X];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x, y;
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++)
        cin >> a[i].u >> a[i].v;
    sort(a + 1, a + n + 1,
    [](item p, item q) {
        return p.u < q.u; 
    });
    memset(f, 0x3f, sizeof f);
    for (int i = n; i > 0; i--) {
        for (int j = 0; j <= y; j++) {
            if (j + a[i].v <= y)
                cmax(g[i][j + a[i].v], g[i + 1][j] + 1);
            cmax(g[i][j], g[i + 1][j]);
        }
        for (int j = 1; j <= y; j++)
            cmax(g[i][j], g[i][j - 1]);
    }
    int res = g[1][y]; f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int miny = y + 1;
        for (int j = 0; j <= x; j++) {
            if (j + a[i].u <= x)
                cmin(f[i][j + a[i].u], f[i - 1][j]);
            cmin(f[i][j], f[i - 1][j] + a[i].v);
        }
        for (int j = 0; j <= x; j++)
            cmin(miny, f[i][j]);
        if (miny <= y)
            cmax(res, i + g[i + 1][y - miny]);
    }
    cout << res << '\n';
}