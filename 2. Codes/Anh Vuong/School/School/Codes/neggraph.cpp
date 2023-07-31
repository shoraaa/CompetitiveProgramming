#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

using ll = long long;
using mat = array <array <ll, 51>, 51>;

const ll inf = 0x3f3f3f3f3f3f3f3f;

mat f, g; int n, m;

void fill(mat &a, ll v = 0) {
    for (int i = 0; i < 51; i++)
        for (int j = 0; j < 51; j++)
            a[i][j] = v;
}

mat operator * (mat a, mat b) {
    mat c; fill(c, inf);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                cmin(c[i][j], a[i][k] + b[k][j]);
    return c;
}

mat pow(mat a, int k) {
    mat res = f;
    for (; k; k >>= 1, a = a * a)
        if (k & 1) res = res * a;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    fill(f, inf); fill(g, inf);
    for (int i = 1; i <= n; i++)
        f[i][i] = g[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        cmin(f[u][v], w);
        cmin(g[u][v], -w);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                cmin(f[i][j], f[i][k] + f[k][j]);
                cmin(g[i][j], f[i][k] + g[k][j]);
                cmin(g[i][j], g[i][k] + f[k][j]);
            }
    int k; cin >> k; g = pow(g, k);
    cout << g[1][n] << '\n';
}