#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define fi first
#define se second

using ii = pair <int, int>;

const int N = 25005;

int a[N], b[N], cnt[2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int x, y; cin >> x >> y;
    int n[2]; cin >> n[0] >> n[1];
    a[n[0]] = x; b[n[1]] = y;
    vector <ii> ed;
    for (int i = 0; i < n[0]; i++)
        cin >> a[i];
    sort(a, a + n[0]);
    for (int i = 0; i < n[0]; i++)
        ed.eb(a[i + 1] - a[i], 0);
    for (int i = 0; i < n[1]; i++)
        cin >> b[i];
    sort(b, b + n[1]);
    for (int i = 0; i < n[1]; i++)
        ed.eb(b[i + 1] - b[i], 1);
    ed.eb(a[0], 0);
    ed.eb(b[0], 1);
    sort(ed.begin(), ed.end());
    long long res = 0;
    for (ii e : ed) {
        if (cnt[1 - e.se] && cnt[e.se])
            res += 1ll * (n[1 - e.se] - cnt[1 - e.se] + 1) * e.fi;
        else res += 1ll * n[1 - e.se] * e.fi;
        cnt[e.se]++;
    }
    cout << res << '\n';
}
