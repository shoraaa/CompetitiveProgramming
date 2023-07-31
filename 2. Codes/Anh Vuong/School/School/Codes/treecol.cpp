#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

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

template <int MOD>
struct modular {
    int v;
    
    modular(): v(0) {}
    
    template <class T>
    modular(T v): v(v % MOD) {
        if (this->v < 0) this->v += MOD;
    }
    
    modular operator - () const {
        return modular() - *this;
    }
    
    modular& operator += (const modular &o) {
        if ((v += o.v) >= MOD) v -= MOD;
        return *this;
    }
    
    modular& operator -= (const modular &o) {
        if ((v -= o.v) < 0) v += MOD;
        return *this;
    }
    
    modular& operator *= (const modular &o) {
        v = ll(v) * o.v % MOD;
        return *this;
    }
    
    modular& operator /= (const modular &o) {
        v = ll(v) * inverse(o.v, MOD) % MOD;
        if (v < 0) v += MOD;
        return *this;
    }
    
    bool operator == (const modular &o) const {
        return v == o.v;
    }
    
    bool operator != (const modular &o) const {
        return v != o.v;
    }
    
    modular operator + (const modular &o) const {
        return modular(*this) += o;
    }
    
    modular operator - (const modular &o) const {
        return modular(*this) -= o;
    }
    
    modular operator * (const modular &o) const {
        return modular(*this) *= o;
    }
    
    modular operator / (const modular &o) const {
        return modular(*this) /= o;
    }
};

template <int MOD>
istream& operator >> (istream &is, modular <MOD> &o) {
    ll v; is >> v; o.v = v;
    if ((o.v %= MOD) < 0) o.v += MOD;
    return is;
}

template <int MOD>
ostream& operator << (ostream &os, const modular <MOD> &o) {
    return os << o.v;
}

template <int MOD, class T>
modular <MOD> pow(modular <MOD> x, T k) {
    modular <MOD> res(1);
    for (; k; k >>= 1, x *= x)
        if (k & 1) res *= x;
    return res;
}

using mint = modular <1000000007>;

const int N = 200005;

vector <int> g[N];
mint dp[N], fac[N], inv[N];
int sz[N];

mint C(int n, int k) {
    return fac[n] * inv[n - k] * inv[k];
}

void dfs(int u, int p) {
    dp[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u); sz[u] += sz[v];
        dp[u] *= dp[v] * C(sz[u], sz[v]);
    }
    sz[u]++;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].eb(v); g[v].eb(u);
    }
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
        inv[i] = inv[i - 1] / i;
    }
    dfs(1, 0); cout << dp[1] << '\n';
}