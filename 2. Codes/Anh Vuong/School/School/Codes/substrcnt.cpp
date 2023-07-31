#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using matrix = array <array <ll, 50>, 50>;

const int K = 55;

char s[K]; int nxt[K][26];
ll n, m;

ll mmul(ll a, ll b) {
    ll q = double(a) * b / m;
    a = (a * b - q * m) % m;
    if (a < 0) a += m;
    return a;
}

ll madd(ll a, ll b) {
    if ((a += b) >= m) a -= m;
    return a;
}

ll msub(ll a, ll b) {
    if ((a -= b) < 0) a += m;
    return a;
}

void reset(matrix &a) {
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            a[i][j] = 0;
}

matrix operator *
(const matrix &a, const matrix &b) {
    matrix c; reset(c);
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            for (int k = 0; k < 50; k++)
                c[i][j] = madd(c[i][j],
                mmul(a[i][k], b[k][j]));
    return c;
}

matrix pow(matrix a, ll k) {
    matrix res; reset(res);
    for (int i = 0; i < 50; i++)
        res[i][i] = 1;
    for (; k; k >>= 1, a = a * a)
        if (k & 1) res = res * a;
    return res;
}

ll mpow(ll a, ll k) {
    ll res = 1;
    for (; k; k >>= 1, a = mmul(a, a))
        if (k & 1) res = mmul(res, a);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> (s + 1);
    ll res = mpow(26, n);
    int k = strlen(s + 1);
    for (int i = 1, j = 0; i <= k; i++) {
        j = nxt[j][s[i] - 'a'];
        nxt[i - 1][s[i] - 'a'] = i;
        for (int c = 0; c < 26; c++)
            nxt[i][c] = nxt[j][c];
    }
    matrix p, q;
    reset(p); reset(q); p[0][0] = 1;
    for (int i = 0; i < k; i++)
        for (int c = 0; c < 26; c++)
            if (nxt[i][c] < k)
                q[i][nxt[i][c]]++;
    p = p * pow(q, n);
    for (int i = 0; i < k; i++)
        res = msub(res, p[0][i]);
    cout << res << '\n';
}