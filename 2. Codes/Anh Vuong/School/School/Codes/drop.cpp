#include <bits/stdc++.h>
using namespace std;

#define ctz __builtin_ctz

using ll = long long;
using matrix = array <array <ll, 55>, 55>;

const int N = 55;
const int LG = 31;

char s[N][N];
bool g[N][N], v[N][N];
int n, m, k, a[N];

void reset(matrix &a) {
    for (int i = 0; i < 55; i++)
        for (int j = 0; j < 55; j++)
            a[i][j] = 0;
}

matrix operator * (const matrix &a, const matrix &b) {
    matrix c; reset(c);
    for (int i = 0; i < 55; i++)
        for (int j = 0; j < 55; j++)
            for (int k = 0; k < 55; k++)
                c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
    return c;
}

matrix pow(matrix a, int n) {
    matrix res; reset(res);
    for (; n; n >>= 1, a = a * a)
        if (n & 1) res = res * a;
    return res;
}

void dfs(int x, int y) {
    if (!x || x > n + 1 || !y || y > m) return;
    if (v[x][y] || s[x][y] == 'X') return;
    v[x][y] = 1;
    if (s[x][y] == '.') dfs(x + 1, y);
    if (s[x][y] == 'L' || s[x][y] == '?')
        dfs(x, y - 1);
    if (s[x][y] == 'R' || s[x][y] == '?')
        dfs(x, y + 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> (s[i] + 1);
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        memset(v, 0, sizeof v);
        dfs(1, i);
        for (int j = 1; j <= m; j++)
            if (v[n + 1][j]) g[i][j] = 1;
    }
    matrix p; reset(p);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            if (g[i][j]) p[i][j] = a[j];
    p = pow(p, k); ll res = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            res = max(res, p[i][j]);
    cout << res << '\n';
}