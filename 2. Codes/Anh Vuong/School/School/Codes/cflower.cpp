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
    if (n < k) return 0;
    return ll(fac[n]) * inv[k] % MOD * inv[n - k] % MOD;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = ll(fac[i - 1]) * i % MOD;
        inv[i] = ll(inv[i - 1]) * inverse(i, MOD) % MOD;
    }
    while (q--) {
        int n, m, k;
        cin >> n >> m >> k;
        int res = 1;
        for (int i = 1; i <= k; i++) {
            res = ll(res) * (m - i + 1) % MOD;
            res = ll(res) * inverse(i, MOD) % MOD;
        }
        int cnt = 0;
        for (int i = 0; i < k; i++)
            if (i & 1)
                (cnt -= ll(k - i) * C(k, i) % MOD *
                mpow(k - i - 1, n - 1) % MOD) %= MOD;
            else (cnt += ll(k - i) * C(k, i) % MOD *
                mpow(k - i - 1, n - 1) % MOD) %= MOD;
        res = ll(res) * cnt % MOD;
        if (res < 0) res += MOD;
        cout << res << '\n';
    }
}