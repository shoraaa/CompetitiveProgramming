#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const long long inf = 1e12;

long long ans;
vector <int> lst[N];
int n, m, p, k, s[N], r[N], ban[N][N];

void cal() {
    long long res = 0;
    for (int i = 1; i <= m; i++) {
        long long en = 0, st = 0;
        int Time = p / s[i] + (p % s[i] != 0);
        for (int u : lst[i]) {
            st = max (en + 1, r[u] + 0LL);
            en = st + Time - 1;
            res = max (res, en);
        }
    }
    ans = min (ans, res);
}

void btrk(int i) {
    if (i == n) { cal(); return; }
    int nxt = i + 1;
    for (int k = 1; k <= m; k++) {
        if (ban[nxt][k]) continue;
        lst[k].push_back (nxt);
        btrk (nxt);
        lst[k].pop_back();
    }
}

vector <int> adj[N];
int pair_lef[N], pair_rig[N*N], used[N];

bool kuhn(int u) {
    if (used[u]) return false;
    used[u] = true;
    for (int v : adj[u]) {
        if (!pair_rig[v] || kuhn (pair_rig[v])) {
            pair_rig[v] = u;
            pair_lef[u] = v;
            return true;
        }
    }
    return false;
}

bool check(long long lim) {
    for (int i = 1; i <= n; i++)
        adj[i].clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (ban[i][j]) continue;
            int Time = p / s[j] + (p % s[j] != 0);
            for (int k = 1; k <= n; k++) {
                long long val = r[i] + 1LL * Time * k;
                if (val <= lim + 1) {
                    adj[i].push_back ((j-1) * n + k);
                }
            }
        }

    memset (pair_rig, 0, sizeof pair_rig);
    memset (pair_lef, 0, sizeof pair_lef);
    bool path_found;
    do {
        path_found = false;
        memset (used, 0, sizeof used);
        for (int i = 1; i <= n; i++) if (!pair_lef[i] && !used[i])
            path_found |= kuhn (i);
    } while (path_found);

    int res = 0;
    for (int i = 1; i <= n; i++) if (pair_lef[i])
        res++;

    return res == n;
}

void full() {
    long long res = -1;
    for (long long low = 0, high = inf; low <= high; ) {
        long long mid = (low + high) >> 1;
        if (check (mid)) res = mid, high = mid - 1;
        else low = mid + 1;
    }
    cout << res << '\n';
}

int main() {
    freopen ("budget.inp", "r", stdin);
    freopen ("budget.out", "w", stdout);

    cin >> m >> n >> p;
    for (int i = 1; i <= m; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++)
        cin >> r[i];
    sort (r+1, r+1+n);
    cin >> k;
    for (int i = 1; i <= k; i++) {
        int u, v; cin >> u >> v;
        ban[u][v] = 1;
    }

    full();

    return 0;
}
