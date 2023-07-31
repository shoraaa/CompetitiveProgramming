#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 105;
const int inf = 0x3f3f3f3f;

int mn[N], a[N], b[N];

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    memset(mn, 0x3f, sizeof mn);
    mn[1] = -1; ll res = 0;
    for (int i = 2; i <= n; i++)
        mn[i] = min(a[1] ^ b[i], a[i] ^ b[1]);
    for (int j = 2; j <= n; j++) {
        int u = 0, ed = inf;
        for (int i = 1; i <= n; i++)
            if (~mn[i] && mn[i] < ed) {
                u = i; ed = mn[i];
            }
        res += mn[u]; mn[u] = -1;
        for (int i = 1; i <= n; i++)
            if (~mn[i] && mn[i] > min(a[u] ^ b[i], a[i] ^ b[u]))
                mn[i] = min(a[u] ^ b[i], a[i] ^ b[u]);
    }
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
