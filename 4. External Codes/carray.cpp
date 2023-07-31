
#include <bits/stdc++.h>

using namespace std;

#define TASK "carray"
#define int long long
#define sqr(x) (1LL*x*x)
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define BIT(x, k) (x >> k & 1)
#define cntBit(x) __builtin_popcountll(x)
#define REP(i,a,b) for (int i = (int) a; i < (int) b; i++)
#define FOR(i,a,b) for (int i = (int) a; i <= (int) b; i++)
#define FORD(i,a,b) for (int i = (int) a; i >= (int) b; i--)

typedef pair <int, int> ii;

const int N = 6e5 + 5;
const int inf = 1e18;

int lef[N][30], rig[N][30], id[N][30];
int n, m, q, cctaone, sz[N], a[N], b[N], v[N];

int get(int u, int p) {
    if (u <= n) return v[u];
    for (int log = 20; log >= 0; log--) {
        if (lef[u][log] <= p && p <= rig[u][log]) {
            p = p - lef[u][log] + 1;
            u = id[u][log];
        }
    }
    if (p <= sz[a[u]])
        return get (a[u], p);
    return get (b[u], p - sz[a[u]]);
}

#undef int
int main() {
#define int long long

    ios :: sync_with_stdio (0);
    cin.tie (0); cout.tie (0);


    freopen (TASK".in", "r", stdin),
    freopen (TASK".out", "w", stdout);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        cin >> v[i], sz[i] = 1, a[i] = i;
    for (int i = n + 1; i <= n + m; i++) {
        cin >> a[i] >> b[i];
        sz[i] = sz[a[i]] + sz[b[i]];
    }

    for (int j = 0; j <= 20; j++)
        for (int i = 1; i <= n; i++)
            lef[i][j] = inf, rig[i][j] = -inf;

    for (int i = n + 1; i <= n + m; i++) {
        int nxt = b[i], L = sz[a[i]] + 1, R = sz[a[i]] + sz[b[i]];
        if (sz[a[i]] >= sz[b[i]]) nxt = a[i], L = 1, R = sz[a[i]];
        id[i][0] = nxt; lef[i][0] = L; rig[i][0] = R;
    }

    for (int j = 1; j <= 20; j++)
        for (int i = n + 1; i <= n + m; i++) {
            id[i][j] = id[id[i][j-1]][j-1];
            lef[i][j] = lef[id[i][j-1]][j-1] + lef[i][j-1] - 1;
            rig[i][j] = rig[id[i][j-1]][j-1] + lef[i][j-1] - 1;
        }

    for (int i = 1; i <= q; i++) {
        int u, p;
        cin >> u >> p;
        cout << get (u, p) << '\n';
    }

    return 0;
}
