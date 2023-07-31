#include <bits/stdc++.h>
using namespace std;

bool a[256], vs[256];
vector <int> g[256];
int y[5005];

bool dfs(int u) {
    if (vs[u]) return 0;
    vs[u] = 1;
    for (int v : g[u])
        if (!y[v] || dfs(y[v])) {
            y[v] = u; return 1;
        }
    return 0;
}

int main() {
    //freopen("input.txt", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    int n, m; string s;
    cin >> n;
    if (n) cin >> s; cin >> m;
    for (char c : s) a[c] = 1; n = 0;
    while (m--) {
        int x = 0; cin >> s;
        while (isdigit(s[0])) {
            x = x * 10 + s[0] - '0';
            s.erase(0, 1);
        }
        for (int i = 1; i <= x; i++)
            for (char c : s)
                g[c].push_back(i + n);
        n += x;
    }
    int mat = 0, add = 0;
    for (int i = 33; i <= 126; i++)
        if (a[i]) {
            memset(vs, 0, sizeof vs);
            mat += dfs(i);
        }
    string res;
    for (int i = 33; i <= 126; i++)
        if (!a[i]) {
            memset(vs, 0, sizeof vs);
            if (dfs(i)) {
                add++; mat++;
                res.push_back(i);
            }
        }
    if (mat == n) {
        cout << add << '\n' << res;
    }
    else cout << "-1\n";
}