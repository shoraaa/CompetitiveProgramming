#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll __lcm(ll a, ll b) {
    return a / __gcd(a, b) * b; 
}

int a[1005], b[1005], d[1005];
vector <int> g[1005];
queue <int> q; bool vs[1005];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, s, t, m;
    cin >> n >> s >> t >> m;
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            if (__lcm(b[i], a[j]) <= n)
                g[i].push_back(j);
    for (int i = 1; i <= m; i++)
        if (s % a[i] == 0) {
            q.push(i); vs[i] = 1;
        }
    while (q.size()) {
        int u = q.front(); q.pop();
        if (t % b[u] == 0) {
            cout << d[u] << '\n';
            return 0;
        }
        for (int v : g[u])
            if (!vs[v]) {
                d[v] = d[u] + 1;
                q.push(v);
            }
    }
    cout << "-1\n";
}