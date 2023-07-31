#include<bits/stdc++.h>
#define forin(i, a, b) for(int i = a; i <= b; i++)
#define forde(i, a, b) for(int i = a; i >= b; i--)
#define forv(a, b) for(auto & a : b)
using namespace std;
const int N = 4e5 + 10;
struct edge {
    int x, y, f, c, w;
};
int n, m, trace[N];
long long d[N];
edge e[N];
vector<int> adj[N];
void input() {
    cin >> n >> m;
    int j = 0;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        e[j++] = {u, v, 0, 1, w};
        e[j++] = {v, u, 0, 0, -w};
        e[j++] = {v, u, 0, 1, w};
        e[j++] = {u, v, 0, 0, -w};
    }
    m = j;
    for(int i = 0; i < m; i++) {
        adj[e[i].x].push_back(i);
    }
}
long long spfa () {
    bool inqueue[N] = {0};
    for(int i = 1; i <= n; i++) d[i] = 1e16;
    d[1] = 0;
    queue<int> q;
    q.push(1);
    inqueue[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = 0;
        forv(t, adj[u]) {
           int v = e[t].y; long long weight = e[t].w;
           int flow = e[t].f, cap = e[t].c;
           if (d[v] <= d[u] + weight || flow == cap) continue;
           d[v] = d[u] + weight;
           trace[v] = t;
           if (!inqueue[v]) {
                q.push(v);
                inqueue[v] = 1;
           }
        }
    }
    return d[n];
}
void incflow() {
    int v = n;
    while (v != 1) {
        int cnt = trace[v];
        int u = e[cnt].x;
        e[cnt].f++;
        e[cnt ^ 1].f--;
        v = u;
    }
}
void dfs(int u, vector<int>  & res) {
    res.push_back(u);
    if (u == n) {
        return;
    }
    forv(t, adj[u]) {
        if (e[t].f == 1) {
            e[t].f--;
            dfs(e[t].y, res);
            break;
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen ("walk.inp", "r")) {
        freopen ("walk.inp", "r", stdin);
        freopen ("walk.out", "w", stdout);
    }
    input();
    int tmp = n;
    long long res = 0;
    vector<int> res1, res2;
    for(int step = 0; step < 2; step++) {
        res += spfa();
        if (trace[n] == 0) {
            cout << -1;
            return 0;
        }
        incflow();
    }
    cout << res << "\n";
    dfs(1, res1);
    dfs(1, res2);
    forv(v, res1) cout << v << " ";
    res2.pop_back();
    reverse(res2.begin(), res2.end());
    forv(v, res2) cout << v << " ";
}
