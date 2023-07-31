#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int st[N], l[N], r[N], tp;
ll s[N], a[N];

void solve() {
    int n; cin >> n;
    ll res = 0; st[tp = 0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        while (tp && a[st[tp]] < a[i]) tp--;
        l[i] = st[tp]; st[++tp] = i;
    }
    st[tp = 0] = n + 1;
    for (int i = n; i > 0; i--) {
        while (tp && a[st[tp]] <= a[i]) tp--;
        r[i] = st[tp]; st[++tp] = i;
    }
    for (int i = 1; i <= n; i++) {
        res += ll(l[i]) * (r[i] - i) % MOD * (a[i] *
        (i - l[i] - 1) % MOD - (s[i - 1] - s[l[i]]) % MOD) % MOD;
        res %= MOD;
    }
    for (int i = n; i > 0; i--) {
        res += ll(n - r[i] + 1) * (i - l[i]) % MOD * (a[i] *
        (r[i] - i - 1) % MOD - (s[r[i] - 1] - s[i]) % MOD) % MOD;
        res %= MOD; 
    }
    cout << (res + MOD) % MOD << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}