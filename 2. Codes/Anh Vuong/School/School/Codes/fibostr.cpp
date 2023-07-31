#include <bits/stdc++.h>
using namespace std;

using matrix = array <array <int, 4>, 4>;
using ll = long long;

const int MOD = 15111992;

int f[1000];

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int cal(const string &a, const string &s) {
    int res = 0;
    for (int i = 0; i + s.size() <= a.size(); i++)
        res += a.substr(i, s.size()) == s;
    return res;
}

int cal(const string &a,
const string &b, const string &s) {
    return cal(a + b, s) - cal(a, s) - cal(b, s);
}

void reset(matrix &a) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            a[i][j] = 0;
}

matrix operator * (const matrix &a, const matrix &b) {
    matrix c; reset(c);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                madd(c[i][j], ll(a[i][k]) * b[k][j] % MOD);
    return c;
}

matrix pow(matrix a, ll n) {
    matrix res; reset(res);
    for (int i = 0; i < 4; i++)
        res[i][i] = 1;
    for (; n; n >>= 1, a = a * a)
        if (n & 1) res = res * a;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    string a, b, s;
    cin >> a >> b >> s;
    int c = 0;
    while (a.size() < s.size() - 1
    || b.size() < s.size() - 1) {
        f[++c] = cal(a, s);
        swap(a, b); b = a + b;
    }
    if (n <= c) {
        cout << f[n] << '\n'; return 0;
    }
    n -= c;
    if (n <= 4) {
        if (n == 1) cout << cal(a, s) << '\n';
        if (n == 2) cout << cal(b, s) << '\n';
        if (n == 3) cout << cal(b + a, s) << '\n';
        if (n == 4) cout << cal(b + a + b, s) << '\n';
        return 0;
    }
    matrix p, q; reset(p); reset(q);
    p[0][0] = cal(b, s);
    p[0][1] = cal(b + a, s);
    p[0][2] = cal(b + a + b, s);
    p[0][3] = cal(a, b, s) + cal(b, b, s);
    q[0][0] = 0; q[0][1] = 0; q[0][2] = 1; q[0][3] = 0;
    q[1][0] = 1; q[1][1] = 0; q[1][2] = 2; q[1][3] = 0;
    q[2][0] = 0; q[2][1] = 1; q[2][2] = 0; q[2][3] = 0;
    q[3][0] = 0; q[3][1] = 0; q[3][2] = 1; q[3][3] = 1;
    p = p * pow(q, n - 4);
    cout << p[0][2] << '\n';
}