#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int h[N][N], f[N][N], x[N][N];

int rec(int x, int y, int a, int b) {
    return h[x][y] - h[x][y - b] -
    h[x - a][y] + h[x - a][y - b];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, a, b, c, d, res = 0, p, q;
    cin >> m >> n >> b >> a >> d >> c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
            h[i][j] += h[i - 1][j] +
            h[i][j - 1] - h[i - 1][j - 1];
        }
    }
    for (int i = c; i <= n; i++)
        for (int j = d; j <= m; j++)
            x[i][j] = rec(i, j, c, d);
    for (int i = c + 1; i <= n; i++) {
        deque <int> dq;
        for (int j = d + 1; j < b - 1; j++) {
            while (dq.size() && x[i][dq.back()] >= x[i][j])
                dq.pop_back();
            dq.push_back(j);
        }
        for (int j = b - 1; j < m; j++) {
            while (dq.size() && dq.front() <= j + d - b + 1)
                dq.pop_front();
            while (dq.size() && x[i][dq.back()] >= x[i][j])
                dq.pop_back();
            dq.push_back(j);
            f[i][j + 1] = x[i][dq.front()];
        }
    }
    for (int j = b; j <= m; j++) {
        deque <int> dq;
        for (int i = c + 1; i < a - 1; i++) {
            while (dq.size() && f[dq.back()][j] >= f[i][j])
                dq.pop_back();
            dq.push_back(i);
        }
        for (int i = a - 1; i < n; i++) {
            while (dq.size() && dq.front() <= i + c - a + 1)
                dq.pop_front();
            while (dq.size() && f[dq.back()][j] >= f[i][j])
                dq.pop_back();
            dq.push_back(i);
            x[i + 1][j] = f[dq.front()][j];
        }
    }
    for (int i = a; i <= n; i++)
        for (int j = b; j <= m; j++)
            if (res < rec(i, j, a, b) - x[i][j]) {
                res = rec(i, j, a, b) - x[i][j];
                p = i; q = j;
            }
    cout << q - b + 1 << ' ' << p - a + 1 << '\n';
    for (int i = p - a + c + 1; i < p; i++)
        for (int j = q - b + d + 1; j < q; j++)
            if (rec(i, j, c, d) == x[p][q]) {
                cout << j - d + 1 << ' ' << i - c + 1 << '\n';
                return 0;
            }
}