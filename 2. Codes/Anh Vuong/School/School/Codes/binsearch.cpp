#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    return u;
}

const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

int mpow(int x, int k) {
    int res = 1;
    for (; k; k >>= 1, x = ll(x) * x % MOD)
        if (k & 1) res = ll(res) * x % MOD;
    return res;
}

int fac[N], inv[N];

int C(int n, int k) {
    if (n < k || n < 0 || k < 0) return 0;
    return ll(fac[n]) * inv[k] % MOD * inv[n - k] % MOD;
}

int P(int n, int k) {
    if (n < k || n < 0 || k < 0) return 0;
    return ll(fac[n]) * inv[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = ll(fac[i - 1]) * i % MOD;
        inv[i] = ll(inv[i - 1]) * inverse(i, MOD) % MOD;
    }
    int n, v, res = 0; cin >> n >> v;
    for (int p = 1; p <= n; p++) {
        int l = 1, r = n;
        int le = 0, gr = 0;
        while (l <= r) {
            int m = (l + r + 1) / 2;
            if (m == p) break;
            if (m < p) {
                le++; l = m + 1;
            }
            else {
                gr++; r = m - 1;
            }
        }
        (res += ll(P(v - 1, le)) * P(n - v, gr) % MOD
        * fac[n - 1 - le - gr] % MOD) %= MOD;
        cerr << le << ' ' << gr << '\n';
    }
    if (res < 0) res += MOD;
    cout << res << '\n';
}