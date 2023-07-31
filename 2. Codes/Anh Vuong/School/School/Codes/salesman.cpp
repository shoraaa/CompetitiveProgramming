#include <bits/stdc++.h>

using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

using ll = long long;

struct market {
    int t; ll l, m;
};

const int N = 500005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll dp[N], bit[2][N];
market a[N];

void update0(int i, ll v) {
    for (i++; i < N; i += i & -i)
        cmax(bit[0][i], v);
}

void update1(int i, ll v) {
    for (i++; i > 0; i -= i & -i)
        cmax(bit[1][i], v);
}

ll query0(int i) {
    ll res = -INF;
    for (i++; i > 0; i -= i & -i)
        cmax(res, bit[0][i]);
    return res;
}

ll query1(int i) {
    ll res = -INF;
    for (i++; i < N; i += i & -i)
        cmax(res, bit[1][i]);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; ll u, d, res;
    cin >> n >> u >> d >> a[0].l;
    for (int i = 1; i <= n; i++)
        cin >> a[i].t >> a[i].l >> a[i].m;
    a[n + 1].l = a[0].l;
    a[0].t = -1; a[n + 1].t = N + 1;
    sort(a + 1, a + n + 1,
    [](market p, market q) {
        return p.t != q.t ? p.t < q.t : p.l < q.l;
    });
    memset(bit, 0xc0, sizeof bit);
    update0(a[0].l, d * a[0].l);
    update1(a[0].l, -u * a[0].l);
    for (int i = 1; i <= n + 1; ) {
        int j = i;
        while (j <= n + 1 && a[i].t == a[j].t) j++;
        vector <ll> tmp(j - i), cur(j - i);
        ll mpro = -INF, pre = 0;
        for (int k = i; k < j; k++) {
            cur[k - i] = max(query0(a[k].l) -
            d * a[k].l, query1(a[k].l) + u * a[k].l);
            if (k == n + 1) res = cur[k - i];
            cmax(mpro, cur[k - i] - pre + d * a[k].l);
            pre += a[k].m;
            tmp[k - i] = pre + mpro - d * a[k].l;
        }
        mpro = -INF; pre = 0;
        for (int k = j - 1; k >= i; k--) {
            cmax(mpro, cur[k - i] - pre - u * a[k].l);
            pre += a[k].m;
            cmax(tmp[k - i], pre + mpro + u * a[k].l);
        }
        for (int k = i; k < j; k++) {
            update0(a[k].l, tmp[k - i] + d * a[k].l);
            update1(a[k].l, tmp[k - i] - u * a[k].l);
        }
        i = j;
    }
    cout << res << '\n';
}