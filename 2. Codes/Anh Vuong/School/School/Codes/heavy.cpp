
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

map <size_t, int> mp[2];
hash <string> hs;
int a[N][N], d[N], x[N], y[N];
queue <int> q; int n, m, k;

bool bfs() {
    fill_n(d + 1, n, -1);
    for (int u = 1; u <= n; u++)
        if (!x[u]) {
            q.emplace(u); d[u] = 0;
        }
    bool flag = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= m; v++) {
            if (!a[u][v]) continue;
            if (!y[v]) flag = true;
            else if (d[y[v]] < 0) {
                d[y[v]] = d[u] + 1;
                q.emplace(y[v]);
            }
        }
    }
    return flag;
}

bool dfs(int u) {
    for (int v = 1; v <= m; v++) {
        if (!a[u][v]) continue;
        if (!y[v] || (d[y[v]] ==
        d[u] + 1 && dfs(y[v]))) {
            x[u] = v; y[v] = u;
            return 1;
        }
    }
    d[u] = -1; return 0;
}

int matching() {
    int res = 0;
    while (bfs()) {
        for (int u = 1; u <= n; u++)
            if (!x[u]) res += dfs(u);
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        size_t pre = hs(s.substr(0, k));
        if (!mp[0].count(pre))
            mp[0][pre] = mp[0].size() + 1;
        size_t suf = hs(s.substr(s.size() - k, k));
        if (!mp[1].count(suf))
            mp[1][suf] = mp[1].size() + 1;
        a[mp[0][pre]][mp[1][suf]] = 1;
    }
    n = mp[0].size(); m = mp[1].size();
    cout << matching() << '\n';
}