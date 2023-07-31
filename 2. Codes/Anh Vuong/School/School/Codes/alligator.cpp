#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

deque <int> row[N], col[N];
char s[N][N];

int main() {
    freopen("alligator.in", "r", stdin);
    freopen("alligator.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n, m, res = 0; cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> (s[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] != '.') {
                row[i].emplace_back(j);
                col[j].emplace_back(i);
            }
    queue <pair <int, int>> q;
    for (int i = 1; i <= n; i++)
        if (row[i].size()) {
            if (s[i][row[i].front()] == 'W') {
                q.emplace(i, row[i].front());
                s[i][row[i].front()] = '.';
            }
            if (s[i][row[i].back()] == 'E') {
                q.emplace(i, row[i].back());
                s[i][row[i].back()] = '.';
            }
        }
    for (int j = 1; j <= m; j++)
        if (col[j].size()) {
            if (s[col[j].front()][j] == 'N') {
                q.emplace(col[j].front(), j);
                s[col[j].front()][j] = '.';
            }
            if (s[col[j].back()][j] == 'S') {
                q.emplace(col[j].back(), j);
                s[col[j].back()][j] = '.';
            }
        }
    while (q.size()) {
        int i, j; tie(i, j) = q.front();
        q.pop(); res++;
        while (row[i].size() &&
        s[i][row[i].front()] == '.')
            row[i].pop_front();
        while (row[i].size() &&
        s[i][row[i].back()] == '.')
            row[i].pop_back();
        while (col[j].size() &&
        s[col[j].front()][j] == '.')
            col[j].pop_front();
        while (col[j].size() &&
        s[col[j].back()][j] == '.')
            col[j].pop_back();
        if (row[i].size()) {
            if (s[i][row[i].front()] == 'W') {
                q.emplace(i, row[i].front());
                s[i][row[i].front()] = '.';
            }
            if (s[i][row[i].back()] == 'E') {
                q.emplace(i, row[i].back());
                s[i][row[i].back()] = '.';
            }
        }
        if (col[j].size()) {
            if (s[col[j].front()][j] == 'N') {
                q.emplace(col[j].front(), j);
                s[col[j].front()][j] = '.';
            }
            if (s[col[j].back()][j] == 'S') {
                q.emplace(col[j].back(), j);
                s[col[j].back()][j] = '.';
            }
        }
    }
    cout << res << '\n';
}