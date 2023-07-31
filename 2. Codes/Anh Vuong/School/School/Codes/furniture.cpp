#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int deg[2][N][N], n, m; 
bool a[N][N]; int cnt[N * 2];


void down(int x, int y) {
    deg[0][x][y] = deg[1][x][y] = 0;
    if (deg[0][x + 1][y]) {
        deg[0][x + 1][y]--;
        if (!deg[0][x + 1][y]) {
            cnt[x + y + 1]--;
            down(x + 1, y);
        }
    }
    if (deg[0][x][y + 1]) {
        deg[0][x][y + 1]--;
        if (!deg[0][x][y + 1]) {
            cnt[x + y + 1]--;
            down(x, y + 1);
        }
    }
}

void up(int x, int y) {
    deg[0][x][y] = deg[1][x][y] = 0;
    if (deg[1][x - 1][y]) {
        deg[1][x - 1][y]--;
        if (!deg[1][x - 1][y]) {
            cnt[x + y - 1]--;
            up(x - 1, y);
        }
    }
    if (deg[1][x][y - 1]) {
        deg[1][x][y - 1]--;
        if (!deg[1][x][y - 1]) {
            cnt[x + y - 1]--;
            up(x, y - 1);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            deg[0][i][j] = deg[1][i][j] = 2;
            if (i == 1) deg[0][i][j]--;
            if (j == 1) deg[0][i][j]--;
            if (i == n) deg[1][i][j]--;
            if (j == m) deg[1][i][j]--;
            cnt[i + j]++;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (!a[i][j] || !deg[0][i][j]
            || !deg[1][i][j]) continue;
            cnt[i + j]--;
            down(i, j); up(i, j);
        }
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        if (a[x][y]) {
            cout << "0\n"; continue;
        }
        if (!deg[0][x][y]) {
            cout << "1\n"; continue;
        }
        if (cnt[x + y] > 1) {
            cnt[x + y]--; a[x][y] = 1;
            down(x, y); up(x, y);
            cout << "1\n";
        } else cout << "0\n";
    }
}
