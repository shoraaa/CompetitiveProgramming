#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

#define fi first
#define se second

using ii = pair <int, int>;

const int N = 1505;
const int r[] = {-1, 0, 1, 0};
const int c[] = {0, 1, 0, -1};
const char *cc[] = {"NO\n", "YES\n"};

int low[N][N], num[N][N], tim;
bool bl[N][N], ans[N][N];
int n, m, q; queue <ii> qq;
ii par[N][N];

void dfs(int x, int y) {
    low[x][y] = num[x][y] = ++tim;
    int u, v;
    for (int k = 0; k < 4; k++) {
        u = x + r[k]; v = y + c[k];
        if (!u || !v || u > n || v > m
        || bl[u][v]) continue;
        if (!num[u][v]) {
            par[u][v] = ii(x, y);
            dfs(u, v);
            cmin(low[x][y], low[u][v]);
        }
        else if (par[x][y] != ii(u, v))
            cmin(low[x][y], num[u][v]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    ii src, sink;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            if (c == '#') bl[i][j] = 1;
            if (c == 'A')
                src = ii(i, j);
            if (c == 'B')
                sink = ii(i, j);
        }
    dfs(src.fi, src.se); qq.push(sink);
    ans[sink.fi][sink.se] = 1;
    while (qq.size()) {
        int x, y, u, v, p, q;
        tie(x, y) = qq.front(); qq.pop();
        for (int k = 0; k < 4; k++) {
            u = x + r[k]; v = y + c[k];
            p = x + r[(k + 2) % 4];
            q = y + c[(k + 2) % 4];
            if (!num[u][v] || ans[u][v]
            || !num[p][q]) continue;
            if (par[p][q] == ii(x, y)
            && low[p][q] >= num[x][y])
                continue;
            ans[u][v] = 1;
            qq.emplace(u, v);
        }
    }
    while (q--) {
        int x, y; cin >> x >> y;
        cout << cc[ans[x][y]];
    }
}