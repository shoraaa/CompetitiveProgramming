#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

struct node {
    int x, y;

    node(int x = 0, int y = 0):
    x(x), y(y) {}
};

const int N = 505;
const int W = 10005;

int a[N][N], d[5][N][N], n, m;
vector <node> v[W];

void dijkstra(int c, int i) {
    for (int w = 0, nw; w < W; w++) {
        while (v[w].size()) {
            node p = v[w].back(), q;
            v[w].pop_back();
            if (w > d[i][p.x][p.y]) continue;
            if (p.x > 1) {
                q = p; q.x--;
                nw = w + abs(c - a[q.x][q.y]);
                if (cmin(d[i][q.x][q.y], nw))
                    v[nw].push_back(q);
            }
            if (p.y > 1) {
                q = p; q.y--;
                nw = w + abs(c - a[q.x][q.y]);
                if (cmin(d[i][q.x][q.y], nw))
                    v[nw].push_back(q);        
            }
            if (p.x < n) {
                q = p; q.x++;
                nw = w + abs(c - a[q.x][q.y]);
                if (cmin(d[i][q.x][q.y], nw))
                    v[nw].push_back(q);
                             
            }
            if (p.y < m) {
                q = p; q.y++;
                nw = w + abs(c - a[q.x][q.y]);
                if (cmin(d[i][q.x][q.y], nw))
                    v[nw].push_back(q);
            }
        }
    }    
}

int compute() {
    int res = INT_MAX;
    for (int c = 0; c < 10; c++) {
        memset(d, 0x3f, sizeof d);
        for (int i = 1; i <= n; i++) {
            d[0][i][1] = abs(a[i][1] - c);
            v[d[0][i][1]].emplace_back(i, 1);
        }
        dijkstra(c, 0);
        for (int j = 1; j <= m; j++) {
            d[1][1][j] = abs(a[1][j] - c);
            v[d[1][1][j]].emplace_back(1, j);
        }
        dijkstra(c, 1);
        for (int i = 1; i <= n; i++) {
            d[2][i][m] = abs(a[i][m] - c);
            v[d[2][i][m]].emplace_back(i, m);
        }
        dijkstra(c, 2);
        for (int j = 1; j <= m; j++) {
            d[3][n][j] = abs(a[n][j] - c);
            v[d[3][n][j]].emplace_back(n, j);
        }
        dijkstra(c, 3);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                d[4][i][j] = d[0][i][j] +
                d[1][i][j] - abs(a[i][j] - c);
                v[d[4][i][j]].emplace_back(i, j);
            }
        dijkstra(c, 4);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                res = min(res, d[4][i][j] +
                d[2][i][j] + d[3][i][j]
                - 2 * abs(a[i][j] - c));
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio();
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            a[i][j] = c - '0';
        }
    int res = compute();
    reverse(a + 1, a + n + 1);
    cmin(res, compute());
    cout << res << '\n';
    
}