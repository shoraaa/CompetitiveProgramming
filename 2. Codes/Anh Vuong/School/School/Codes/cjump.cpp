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

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int fac[N], inv[N];

int C(int n, int k) {
    if (n < k) return 0;
    return ll(fac[n]) * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = ll(fac[i - 1]) * i % MOD;
        inv[i] = ll(inv[i - 1]) * inverse(i, MOD) % MOD;
    }
    int n, k, res = 0; cin >> n >> k;
    for (int i = 0; i <= k; i++)
        if ((k - i * 2) % n == 0)
            (res += C(k, i)) %= MOD;
    if (res < 0) res += MOD;
    cout << res << '\n';
}