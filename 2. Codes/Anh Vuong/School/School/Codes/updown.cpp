#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int f[N], g[N], bit[N], a[N];

void update(int i) {
    for (; i > 0; i -= i & -i)
        bit[i]++;
}

int query(int i) {
    int res = 0;
    for (; i < N; i += i & -i)
        res += bit[i];
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; update(a[i]);
        f[i] = query(a[i] + 1);
    }
    memset(bit, 0, sizeof bit);
    long long res = 0;
    for (int i = n; i > 0; i--) {
        update(a[i]);
        g[i] = query(a[i] + 1);
        res += min(f[i], g[i]);
    }
    cout << res << '\n';
}
