#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

const int N = 305;

vector <pair <int, int>> blocks[N];
int f[N][N][2], g[N][N][2], a[N][N];
int n, m, q, ans[N * N], cur, mx;

void input() {
    cin >> m >> n >> q;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            a[j][i] = c - 'A';
        }
}

int cost(int pts, int val) {
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        if (int(blocks[i].size()) < pts) continue;
        int add = g[i][pts][val];
        for (int j = 0; j < pts; j++)
            cmin(add, min(g[i][j][0], g[i][j][1]));
        tot += add;
    }
    return tot;
}

void calc_cost(int pts) {
    int lim = min(cost(pts, 0), cost(pts, 1));
    while (cur >= lim) {
        ans[cur] = pts; cur--;
    }
}

void pre_calc() {
    mx = 0; cur = n * m;
    for (int i = 1; i <= n; i++)
        mx = max(mx, int(blocks[i].size()) + 1);
    for (int i = 1; i <= mx; i++) {
        calc_cost(i); if (cur < 0) break;
    }
}

void query() {
    while (q--) {
        int k; cin >> k; cout << ans[k] << ' ';
    }
    cout << '\n';
}

void calc_cols() {
    for (int i = 1; i <= n; i++) {
        int cnt = 0, val;
        a[i][m + 1] = 2;
        blocks[i].clear();
        for (int j = 1; j <= m; j++) {
            cnt++;
            if (a[i][j] != a[i][j + 1]) {
                blocks[i].push_back({cnt, a[i][j]});
                cnt = 0;
            }
        }
        int l = blocks[i].size();
        f[l][0][1] = f[l][0][0] = 0;
        for (int k = 0; k <= l; k++) {
            for (int j = l - 1; j >= 0; j--) {
                tie(cnt, val) = blocks[i][j];
                if (k == 0) {
                    f[j][0][0] = f[j + 1][0][0] + cnt;
                 f[j][0][1] = f[j + 1][0][1] + cnt;
                }
                else {
                    f[j][k][val] = min(f[j + 1][k][val],
                    f[j + 1][k - 1][1 - val]);
                    f[j][k][1 - val] =
                    f[j + 1][k][1 - val] + cnt;
                }
            }
            g[i][k][0] = f[0][k][0];
            g[i][k][1] = f[0][k][1];
        }
    }
}


void solve() {
    input(); calc_cols(); pre_calc(); query();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}