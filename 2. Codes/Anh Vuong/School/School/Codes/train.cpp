#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

#define eb emplace_back

using ii = pair <int, int>;

const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

vector <ii> adj[N], dag[N];
int d[N], n, m, q, dp[N];
int tim[N], ord[N], cnt[N];

void input() {
    memset(tim, 0x3f, sizeof tim);
    memset(d, 0x3f, sizeof d);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].eb(v, i);
        adj[v].eb(u, i);
    }
    for (int i = 1; i <= q; i++) {
        int j; cin >> j; tim[j] = i;
    }
}

void bfs() {
    queue <int> q;
    memset(d, 0x3f, sizeof d);
    d[1] = 0; q.emplace(1);
    while (q.size()) {
        int u = q.front();
        q.pop(); int v, i;
        for (ii e : adj[u]) {
            tie(v, i) = e;
            if (d[v] == inf) {
                d[v] = d[u] + 1;
                q.emplace(v);
            }
        }
    }
}

void build_dag() {
    for (int u = 1; u <= n; u++) {
        int v, i;
        for (ii e : adj[u]) {
            tie(v, i) = e;
            if (d[v] == d[u] + 1)
                dag[u].eb(v, i);
        }
    }
}

void process() {
    bfs(); build_dag();
    for (int i = 1; i <= n; i++)
        ord[i] = i;
    sort(ord + 1, ord + n + 1,
    [&](int x, int y) {
        return d[x] < d[y];
    });
    dp[1] = inf;
    for (int j = 1; j <= n; j++) {
        int v, i, u = ord[j];
        for (ii e : dag[u]) {
            tie(v, i) = e;
            cmax(dp[v], min(dp[u], tim[i]));
        }
    }
    for (int u = 1; u <= n; u++) {
        if (dp[u] < inf) cnt[dp[u]]++;
    }
}

void output() {
    int cur = 0;
    for (int i = 1; i <= q; i++) {
        cur += cnt[i];
        cout << cur << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    input(); process(); output();
}