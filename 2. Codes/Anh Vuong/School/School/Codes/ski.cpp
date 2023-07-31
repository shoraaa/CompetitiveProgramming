#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

using ll = long long;

const int N = 55;

ll d[N][N], h[N];
int a[N][N], n;
const ll inf = 1e18;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            a[i][j] = c - '0';
        }
    for (int i = 1; i <= n; i++)
        cin >> h[i];
}

ll dijkstra() {
    memset(d, 0x3f, sizeof d);
    for (int i = 1; i <= n; i++)
        d[1][i] = abs(h[i] - h[1]);
    while (true) {
        int u = 0, t = 0; ll res = inf;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (~d[i][j] && d[i][j] < res) {
                    res = d[i][j]; u = i; t = j;
                }
        if (!u) break; if (u == n) return res;
        for (int i = 1; i <= n; i++) {
            if (!a[u][i]) continue;
            for (int j = 1; j <= n; j++)
                if (h[j] <= h[t]) cmin(d[i][j],
                res + abs(h[j] - h[i]));
        }
        d[u][t] = -1;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    input(); cout << dijkstra() << '\n';
}