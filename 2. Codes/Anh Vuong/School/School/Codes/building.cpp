#include <bits/stdc++.h>
using namespace std;

#define lb lower_bound
#define ub upper_bound
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
#define eb emplace_back

using ii = pair <int, int>;

struct rec {
    int x, y, u, v;
};

const int N = 2e5 + 5;

vector <int> cmpx, cmpy;
rec a[N]; vector <int> cur;
vector <int> adj[N];
vector <ii> pos[N];
int num[N], low[N], sz[N], tim;

void dfs(int u, int p = 0) {
    num[u] = low[u] = ++tim; sz[u] = 1;
    for (int v : adj[u])
        if (!num[v]) {
            dfs(v, u); sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u]) cur.eb(v);
        }
        else if (v != p)
            low[u] = min(low[u], num[v]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, res = INT_MAX; cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        swap(y, v);
        a[i] = {x, y, u, v};
        cmpx.push_back(x);
        cmpy.push_back(y);
        cmpx.push_back(u);
        cmpy.push_back(v);
    }
    sort(all(cmpx)); sort(all(cmpy));
    cmpx.erase(unique(all(cmpx)), cmpx.end());
    cmpy.erase(unique(all(cmpy)), cmpy.end());
    for (int i = 1; i <= n; i++) {
        a[i].x = ub(all(cmpx), a[i].x) - cmpx.begin();
        a[i].u = ub(all(cmpx), a[i].u) - cmpx.begin();
        a[i].y = ub(all(cmpy), a[i].y) - cmpy.begin();
        a[i].v = ub(all(cmpy), a[i].v) - cmpy.begin();
    }
    for (int i = 1; i <= n; i++) {
        pos[a[i].x].eb(a[i].y, i);
        pos[a[i].x].eb(a[i].v, i);
        pos[a[i].u].eb(a[i].y, i);
        pos[a[i].u].eb(a[i].v, i);
    }
    for (int i = 1; i <= 2 * n; i++)
        sort(pos[i].begin(), pos[i].end());
    for (int i = 1; i <= n; i++) {
        for (auto it = lb(all(pos[a[i].x]), ii(a[i].y, 0));
        it < ub(all(pos[a[i].x]), ii(a[i].v, 0)); it++)
            if (it->se != i) {
                adj[i].eb(it->se);
                adj[it->se].eb(i);
            }
        for (auto it = lb(all(pos[a[i].u]), ii(a[i].y, 0));
        it < ub(all(pos[a[i].u]), ii(a[i].v, 0)); it++)
            if (it->se != i) {
                adj[i].eb(it->se);
                adj[it->se].eb(i);
            }
    }
    for (int i = 1; i <= 2 * n; i++)
        pos[i].clear();
    for (int i = 1; i <= n; i++) {
        pos[a[i].y].eb(a[i].x, i);
        pos[a[i].y].eb(a[i].u, i);
        pos[a[i].v].eb(a[i].x, i);
        pos[a[i].v].eb(a[i].u, i);
    }
    for (int i = 1; i <= 2 * n; i++)
        sort(pos[i].begin(), pos[i].end());
    for (int i = 1; i <= n; i++) {
        for (auto it = lb(all(pos[a[i].y]), ii(a[i].x, 0));
        it < ub(all(pos[a[i].y]), ii(a[i].u, 0)); it++)
            if (it->se != i) {
                adj[i].eb(it->se);
                adj[it->se].eb(i);
            }
        for (auto it = lb(all(pos[a[i].v]), ii(a[i].x, 0));
        it < ub(all(pos[a[i].v]), ii(a[i].u, 0)); it++)
            if (it->se != i) {
                adj[i].eb(it->se);
                adj[it->se].eb(i);
            }
    }
    for (int i = 1; i <= n; i++)
        if (!num[i]) {
            cur.clear(); dfs(i);
            for (int j : cur)
                res = min(res, abs(sz[i] - 2 * sz[j]));
        }
    if (res == INT_MAX) res = -1;
    cout << res << '\n';
}
