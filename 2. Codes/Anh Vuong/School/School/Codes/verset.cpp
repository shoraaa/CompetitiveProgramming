#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define eb emplace_back

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

using ii = pair <int, int>;
using ll = long long;

struct edge {
    int u, v;
};

const int N = 200005;
const int M = 200005;
const int DIV = 5e8 + 4;
const int MOD = 1e9 + 7;

edge ed[M];
vector <ii> adj[N];
bool brid[N];
int comp[N], deg[N], cnt[N];
int num[N], low[N], tim;

void dfs1(int u, int e) {
    num[u] = low[u] = ++tim;
    int v, i;
    for (ii p : adj[u]) {
        tie(v, i) = p;
        if (i == e) continue;
        if (num[v])
            cmin(low[u], num[v]);
        else {
            dfs1(v, i);
            cmin(low[u], low[v]);
            if (num[u] < low[v])
                brid[i] = 1;
        }
    }
}

void dfs2(int u, int cc) {
    if (comp[u]) return;
    comp[u] = cc; cnt[cc]++;
    for (ii p : adj[u])
        if (!brid[p.se])
            dfs2(p.fi, cc);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> ed[i].u >> ed[i].v;
        adj[ed[i].u].eb(ed[i].v, i);
        adj[ed[i].v].eb(ed[i].u, i);
    }
    dfs1(1, 0); int cc = 0;
    for (int i = 1; i <= n; i++)
        if (!comp[i]) dfs2(i, ++cc);
    for (int i = 1; i <= m; i++)
        if (brid[i]) {
            deg[comp[ed[i].u]]++;
            deg[comp[ed[i].v]]++;
        }
    int ans = 0; ll prod = 1;
    for (int i = 1; i <= cc; i++)
        if (deg[i] == 1) {
            ans++;
            prod = prod * cnt[i] % MOD;
        }
    if (!ans) cout << 1 << ' ' << n << '\n';
    else cout << ans << ' ' << prod << '\n';
}
