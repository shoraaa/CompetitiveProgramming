#include <bits/stdc++.h>
using namespace std;

#define lb lower_bound
#define ub upper_bound

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

struct seg {
    ll l, h1, h2;
    
    seg(ll l, ll h1, ll h2):
    l(l), h1(h1), h2(h2) {}
    
    bool operator < (const seg &o) const {
        return l < o.l;
    }
};

const int N = 1e6 + 5;
const ll inf = 1e18;

ll l[N], r[N], h[N];
set <seg> s;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    mint res, ans = 1;
    s.emplace(-1, 0, 0);
    s.emplace(inf, 0, 0);
    for (int i = 0; i < n; i++)
        cin >> l[i];
    for (int i = 0; i < n; i++) {
        cin >> r[i]; r[i] += l[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        res += (r[i] - l[i] + h[i]) * 2;
        auto it = prev(s.lb({l[i], -1, -1}));
        auto pt = s.ub({r[i], -1, -1});
        auto le = *it, ri = *pt;
        while (it->l < ri.l) {
            pt = it++;
            if (pt->h2)
                res -= (min(r[i], it->l) -
                max(l[i], pt->l)) * 2;
            if (pt->l >= l[i]) {
                res -= abs(pt->h1 - pt->h2);
                s.erase(pt);
            }
        }
        res -= le.h2 + ri.h1;
        if (le.h2 != h[i])
            s.emplace(l[i], le.h2, h[i]);
        if (ri.h1 != h[i])
            s.emplace(r[i], h[i], ri.h1);
        ans *= res;
    }
    cout << ans << '\n';
}