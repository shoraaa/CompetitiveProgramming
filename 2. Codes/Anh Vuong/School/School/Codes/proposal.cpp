#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

struct cc {
    int x, y, z;
    
    cc(int x, int y, int z):
    x(x), y(y), z(z) {}
    
    cc() {}
};

const int N = 305;

vector <cc> up[N];
vector <cc> down[N];
vector <cc> mx;
int a[N][N], b[N][N], c[N][N];
int n, m, k;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(6);
    cout << fixed;
    cin >> n >> m >> k;
    int max_size = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> b[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];
    if (n == 1) {
        int x = 0, y = 0, z = 0;
        for (int i = 1; i <= m; i++) {
            x += a[1][i]; y += b[1][i]; z += c[1][i];
        }
        if (z <= k) cout << double(x) / y << '\n';
        else cout << "-1\n"; return 0;
    }
    {
        stack <tuple <int, int, int, int, int>,
        vector <tuple <int, int, int, int, int>>> st;
        st.emplace(1, 1, 0, 0, 0);
        int i, j, x, y, z;
        while (st.size()) {
            tie(i, j, x, y, z) = st.top(); st.pop();
            x += a[i][j]; y += b[i][j]; z += c[i][j];
            if (i == n / 2) up[j].eb(x, y, z);
            if (i < n / 2)
                st.emplace(i + 1, j, x, y, z);
            if (j < m)
                st.emplace(i, j + 1, x, y, z);
        }
        st.emplace(n, m, 0, 0, 0);
        while (st.size()) {
            tie(i, j, x, y, z) = st.top(); st.pop();
            x += a[i][j]; y += b[i][j]; z += c[i][j];
            if (i == n / 2 + 1) down[j].eb(x, y, z);
            if (i > n / 2 + 1)
                st.emplace(i - 1, j, x, y, z);
            if (j > 1)
                st.emplace(i, j - 1, x, y, z);
        }
    }
    auto cmp = [](cc p, cc q) {
        return p.z < q.z;
    };
    for (int j = 1; j <= m; j++) {
        sort(up[j].begin(), up[j].end(), cmp);
        sort(down[j].begin(), down[j].end(), cmp);
        max_size = max(max_size, int(up[j].size()));
    }
    mx.resize(max_size);
    double lo = 0, hi = 1e6, mi;
    double ans, flag = 0;
    auto comp = [&](cc p, cc q) {
        return double(p.x) - mi * p.y
        < double(q.x) - mi * q.y;
    };
    for (int st = 0; st < 50; st++) {
        mi = (lo + hi) / 2;
        bool ok = 0;
        for (int j = 1; j <= m; j++) {
            mx[0] = up[j][0];
            for (int x = 1; x < up[j].size(); x++) {
                if (comp(mx[x - 1], up[j][x]))
                    mx[x] = up[j][x];
                else mx[x] = mx[x - 1];
            }
            int x = up[j].size() - 1;
            for (int y = 0; y < down[j].size(); y++) {
                while (~x && up[j][x].z + down[j][y].z > k) x--;
                if (~x && double(mx[x].x + down[j][y].x)
                >= mi * (mx[x].y + down[j][y].y)) ok = 1;
            }
        }
        if (ok) {
            flag = 1; ans = lo = mi;
        }
        else hi = mi;
    }
    if (flag) cout << ans << '\n';
    else cout << "-1\n";
}