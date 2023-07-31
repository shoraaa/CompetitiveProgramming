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

using ll = long long;

struct edge {
    int u, v; ll w, t;
};

const int N = 105;
const int K = 1005;
const int M = 10005;
const ll inf = 1e12;

ll f[N][N], d[N], b[N][K], s[N][K];
edge ed[M]; int n, m, k;

void input() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f[i][j] = inf;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            cin >> b[i][j] >> s[i][j];
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v >> f[u][v];
    }
}

void process() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cmin(f[i][j], f[i][k] + f[k][j]);
    m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (i == j || f[i][j] >= inf) continue;
            ll mx = 0;
            for (int x = 1; x <= k; x++)
                if (b[i][x] >= 0 && s[j][x] >= 0)
                    mx = max(mx, s[j][x] - b[i][x]);
            ed[m++] = {i, j, mx, f[i][j]};
        }
    ll lo = 0, hi = 1e9;
    while (lo < hi) {
        ll mi = (lo + hi + 1) / 2;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] = -inf;
        for (int i = 0; i < m; i++)
            f[ed[i].u][ed[i].v] = ed[i].w - ed[i].t * mi;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    cmax(f[i][j], f[i][k] + f[k][j]);
        bool flag = 0;
        for (int i = 1; i <= n; i++)
            if (f[i][i] >= 0) flag = 1;
        if (flag) lo = mi; else hi = mi - 1;
    }
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    input(); process();
}