#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    return u;
}

const int N = 18;
const int V = 300005;
const int MOD = 1e9 + 7;

int a[V], fac[V], inv[V];

int P(int n, int k) {
    if (n < k || k < 0 || n < 0) return 0;
    return ll(fac[n]) * inv[n - k] % MOD;
}

int C(int n, int k) {
    if (n < k || n < 0 || k < 0) return 0;
    return ll(fac[n]) * inv[k]
    % MOD * inv[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    fac[0] = inv[0] = 1;
    for (int i = 1; i < V; i++) {
        fac[i] = ll(fac[i - 1]) * i % MOD;
        inv[i] = ll(inv[i - 1])
        * inverse(i, MOD) % MOD;
    }
    int n, res = 0;
    cin >> n; int m = 1 << n;
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    for (int b = 0; b < n; b++) {
        int cur = 0;
        int mul = (1ll << (n - b)) *
        fac[1 << b] % MOD *
        fac[(1 << n) - (1 << (b + 1))]
        % MOD * fac[1 << b] % MOD;
        for (int i = 1; i <= m; i++) {
            res += ll(cur) * a[i] % MOD
            * C(m - i, (1 << b) - 1)
            % MOD * mul % MOD;
            if (res >= MOD) res -= MOD;
            if (res < 0) res += MOD;
            cur += ll(C(m - i - (1 << b),
            (1 << b) - 1)) * a[i] % MOD;
            if (cur >= MOD) cur -= MOD;
            if (cur < 0) cur += MOD;
        }
    }
    cout << res << '\n';
}