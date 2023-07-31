#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

struct node {
    int x = 0, y = 0;

    node() {}

    node(int x, int y): x(x), y(y) {}
};

struct path {
    int x, y, w;

    path() {}

    path(int x, int y, int w): x(x), y(y), w(w) {}

    bool operator < (const path &o) const {
        return w > o.w;
    }
};

const int N = 505;
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};
const int inf = 0x3f3f3f3f;

int a[N][N], port[4][N][N], dis[N][N];
queue <node> q; node src, sink;
priority_queue <path> pq;
node nxt[4][N][N];

node portal(node t, int k) {
    if (nxt[k][t.x][t.y].x)
        return nxt[k][t.x][t.y];
    node z = {t.x + dx[k], t.y + dy[k]};
    if (!a[z.x][z.y]) return t;
    return nxt[k][t.x][t.y] = portal(z, k);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            a[i][j] = c != '#';
            if (c == 'C') src = {i, j};
            if (c == 'F') sink = {i, j};
        }
    memset(dis, 0x3f, sizeof dis);
    pq.emplace(src.x, src.y, 0);
    while (pq.size()) {
        path t = pq.top(); pq.pop();
        if (dis[t.x][t.y] < t.w) continue;
        int add = INT_MAX; node u(t.x, t.y);
        for (int k = 0; k < 4; k++) {
            node v = portal(u, k);
            cmin(add, abs(u.x - v.x) + abs(u.y - v.y));
            int x = t.x + dx[k], y = t.y + dy[k];
            if (!a[x][y]) continue;
            if (cmin(dis[x][y], t.w + 1))
                pq.emplace(x, y, t.w + 1);
        }
        for (int k = 0; k < 4; k++) {
            node v = portal(u, k);
            if (cmin(dis[v.x][v.y], t.w + add + 1))
                pq.emplace(v.x, v.y, t.w + add + 1);
        }
    }
    if (dis[sink.x][sink.y] == inf) cout << "gameover\n";
    else cout << dis[sink.x][sink.y] << '\n';
}