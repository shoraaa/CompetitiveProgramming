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

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int fac[N], inv[N];

int C(int n, int k) {
    if (n < k || n < 0 || k < 0) return 0;
    return ll(fac[n]) * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = ll(fac[i - 1]) * i % MOD;
        inv[i] = ll(inv[i - 1]) * inverse(i, MOD) % MOD;
    }
    int q; cin >> q;
    while (q--) {
        int n, m, k; cin >> n >> m >> k;
        if (n == m) {
            cout << "1\n"; continue;
        }
        int res = C(n - m - 1, n - m - k);
        res = ll(res) * C(m + 1, m - k + 1) % MOD;
        if (res < 0) res += MOD;
        cout << res << '\n';
    }
}