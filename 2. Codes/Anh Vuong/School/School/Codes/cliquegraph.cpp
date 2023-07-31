#include <bits/stdc++.h>
using namespace std;

using ii = pair <int, int>;

const int N = 10005;

vector <ii> g[N];
deque <int> dq; int d[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int s; cin >> s;
        for (int j = 1; j <= s; j++) {
            int u; cin >> u; u++;
            g[u].emplace_back(n + i, 0);
            g[n + i].emplace_back(u, 1);
        }
    }
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        for (int u = 1; u <= n + m; u++)
            d[u] = -1;
        dq.push_back(i); d[i] = 0;
        while (dq.size()) {
            int u = dq.front(), v, w;
            dq.pop_front();
            for (ii p : g[u]) {
                tie(v, w) = p;
                if (d[v] < 0) {
                    d[v] = d[u] + w;
                    if (w > 0)
                        dq.push_back(v);
                    else dq.push_front(v);
                }
            }
        }
        for (int u = 1; u <= n; u++)
            res += d[u];
    }
    cout << res / 2 << '\n';
}