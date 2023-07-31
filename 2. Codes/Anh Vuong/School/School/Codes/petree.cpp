#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define popcnt __builtin_popcountll
#define fi first
#define se second

using ii = pair <int, int>;
using ll = long long;

const int N = 55;

int s[N]; ll mask[N][N];
vector <ii> g[N];
ii ed[N];

void dfs(int u, int p, int r) {
    int v, i;
    for (ii e : g[u]) {
        tie(v, i) = e;
        if (v == p) continue;
        mask[r][v] = mask[r][u] | 1ll << i;
        dfs(v, u, r);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    ll res = 1ll << (n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].eb(v, i); g[v].eb(u, i);
    }
    for (int i = 1; i <= n; i++)
        dfs(i, 0, i);
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].fi >> ed[i].se;
    }
    for (int i = 1; i < (1 << m); i++) {
        ll ans = 0;
        for (int j = 0; j < m; j++)
            if (i >> j & 1)
                ans |= mask[ed[j].fi][ed[j].se];
        if (popcnt(i) & 1)
            res -= 1ll << (n - 1 - popcnt(ans));
        else res += 1ll << (n - 1 - popcnt(ans));
    }
    cout << res << '\n';
}