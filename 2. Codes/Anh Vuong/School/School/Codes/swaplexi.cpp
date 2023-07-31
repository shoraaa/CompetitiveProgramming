#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 250005;
const int inf = 1e9;

int a[N], cn[N * 4], mn[N * 4];
int lo, hi;

void init(int i, int l, int r) {
    if (l == r) {
        cn[i] = 1; mn[i] = l;
        return;
    }
    int m = (l + r) / 2;
    int ls = i * 2, rs = ls + 1;
    init(ls, l, m);
    init(rs, m + 1, r);
    cn[i] = cn[ls] + cn[rs];
    if (a[mn[ls]] <= a[mn[rs]])
        mn[i] = mn[ls];
    else mn[i] = mn[rs];
}

void update(int i, int l, int r, int p) {
    if (l == r) {
        cn[i] = mn[i] = 0; return;
    }
    int m = (l + r) / 2;
    int ls = i * 2, rs = ls + 1;
    if (m < p)
        update(rs, m + 1, r, p);
    else update(ls, l, m, p);
    cn[i] = cn[ls] + cn[rs];
    if (a[mn[ls]] <= a[mn[rs]])
        mn[i] = mn[ls];
    else mn[i] = mn[rs];
}

int get_pos(int i, int l, int r, int k) {
    if (l == r) return l;
    int m = (l + r) / 2;
    if (cn[i * 2] >= k)
        return get_pos(i * 2, l, m, k);
    return get_pos(i * 2 + 1,
    m + 1, r, k - cn[i * 2]);
}

int get_min(int i, int l, int r) {
    if (l > hi || r < lo) return 0;
    if (l >= lo && r <= hi) return mn[i];
    int m = (l + r) / 2;
    int ql = get_min(i * 2, l, m);
    int qr = get_min(i * 2 + 1, m + 1, r);
    return a[ql] <= a[qr] ? ql : qr;
}

int get_cnt(int i, int l, int r) {
    if (l > hi || r < lo) return 0;
    if (l >= lo && r <= hi) return cn[i];
    int m = (l + r) / 2;
    return get_cnt(i * 2, l, m)
    + get_cnt(i * 2 + 1, m + 1, r);
}

void solve() {
    int n; long long k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    init(1, 1, n); lo = 1;
    for (int i = 1; i <= n; i++) {
        hi = get_pos(1, 1, n,
        min(k + 1, ll(cn[1])));
        int j = get_min(1, 1, n);
        cout << a[j] << " \n"[i == n];
        update(1, 1, n, j);
        hi = j; k -= get_cnt(1, 1, n);
    }
}

int main() {
    freopen("swaplexi.in", "r", stdin);
    freopen("swaplexi.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t; a[0] = inf;
    while (t--) solve();
}
