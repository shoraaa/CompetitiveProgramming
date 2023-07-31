#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using matrix = array <array <int, 53>, 53>;

const int MOD = 1e9 + 7;

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

matrix operator * (const matrix &a, const matrix &b) {
    matrix c;
    for (int i = 0; i < 53; i++)
        for (int j = 0; j < 53; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 53; k++)
                madd(c[i][j], ll(a[i][k]) * b[k][j] % MOD);
        }
    return c;
}

matrix pow(matrix a, ll n) {
    matrix res;
    for (int i = 0; i < 53; i++)
        for (int j = 0; j < 53; j++)
            res[i][j] = 0;
    for (int i = 0; i < 53; i++)
        res[i][i] = 1;
    for (; n; n >>= 1, a = a * a)
        if (n & 1) res = res * a;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n; int k; cin >> n >> k;
    matrix a, b;
    for (int i = 0; i <= k; i++)
        a[0][i] = 1;
    for (int i = 0; i <= k; i++)
        b[0][i] = b[i][i] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = i + 1; j <= k; j++) {
            b[i][j] = b[i - 1][j - 1] + b[i][j - 1];
            if (b[i][j] >= MOD) b[i][j] -= MOD;
        }
    b[k + 1][k + 1] = b[k][k + 1] = 1;
    a = a * pow(b, n);
    cout << a[0][k + 1] << '\n';
}