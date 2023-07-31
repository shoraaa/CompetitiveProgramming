#include <bits/stdc++.h>
using namespace std;

struct trans {
    int u, v, w;
    
    trans(int u, int v, int w):
    u(u), v(v), w(w) {}
};

const int MOD = 1e9 + 7;
const int B = 200;

int a[13], id[1600000];
vector <pair <int, int>> edge;
vector <pair <int, int>> adj[5000];
int dp[2][5000][B];
vector <trans> qq;

void madd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, b; cin >> n >> m >> b;
    int node = 0, mx = 1;
    if (m > n) swap(m, n);
    for (int i = 0; i < m; i++) mx = mx * 3;
    for (int x = 0; x < mx; x++) {
        int y = x; bool ok = 1;
        for (int i = 0; i < m; i++) {
            a[i] = y % 3; y /= 3;
        }
        for (int i = 1; i < m; i++)
            if (a[i] && a[i - 1]) ok = 0;
        for (int i = 1; i < m - 1; i++) {
            if (a[i + 1] == 1 &&
            a[i - 1] == 1) ok = 0;
            if (a[i + 1] == 2 &&
            a[i - 1] == 2) ok = 0;
        }
        if (ok) {
            id[x] = node++;
            for (y = 0; y < (1 << m); y++) {
                bool flag = 1;
                for (int i = 0; i < m; i++)
                    if (a[i] && (y >> i & 1)) {
                        flag = 0; break;
                    }
                for (int i = 1; i < m; i++) {
                    if ((y >> i & 1) && (y >> (i - 1) & 1)) {
                        flag = 0; break;
                    }
                    if ((y >> (i - 1) & 1) && a[i] == 1) {
                        flag = 0; break;
                    }
                    if ((y >> i & 1) && a[i - 1] == 1) {
                        flag = 0; break;
                    }
                }
                for (int i = 1; i < m - 1; i++)
                    if ((y >> (i + 1) & 1) && (y >> (i - 1) & 1)) {
                        flag = 0; break;
                    }
                if (flag) edge.emplace_back(x, y);
            }
        }
    }
    for (auto p : edge) {
        int x, y, z = 0, pw = 1; tie(x, y) = p;
        for (int i = 0; i < m; i++) {
            z += ((x / pw % 3 & 1) * 2 + (y >> i & 1)) * pw;
            pw *= 3;
        }
        qq.emplace_back(id[x], id[z], __builtin_popcount(y));
    }
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        memset(dp[i & 1], 0, sizeof dp[i & 1]);
        for (auto e : qq)
            for (int j = 0; j < B - e.w; j++)
                madd(dp[i & 1][e.v][j + e.w], dp[~i & 1][e.u][j]);
    }
    int res = 0;
    for (int u = 0; u < node; u++)
        for (int j = b; j < B; j++)
            madd(res, dp[n & 1][u][j]);
    cout << res << '\n';
}