#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

struct segment {
    int l, r;

    bool operator < (const segment &o) const {
        return l != o.l ? l < o.l : r < o.r;
    }
};

const int N = 4e5 + 5;
const int LG = 19;

int nxt[LG][N], rmq[LG][N], jump[N];
segment seg[N], que[N];
int n, k, q; vector <int> vals;

int query(int l, int r) {
    if (l > r) return 0;
    int b = __lg(r - l + 1);
    return max(rmq[b][l],
    rmq[b][r + 1 - (1 << b)]);
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q >> k;
    for (int i = 0; i < n; i++) {
        cin >> seg[i].l >> seg[i].r;
        vals.push_back(seg[i].l);
        vals.push_back(seg[i].r);
    }
    for (int i = 0; i < q; i++) {
        cin >> que[i].l >> que[i].r;
        vals.push_back(que[i].l);
        vals.push_back(que[i].r);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(),
    vals.end()), vals.end());
    for (int i = 0; i < n; i++) {
        seg[i].l = lower_bound(vals.begin(),
        vals.end(), seg[i].l) - vals.begin();
        seg[i].r = lower_bound(vals.begin(),
        vals.end(), seg[i].r) - vals.begin();
    }
    for (int i = 0; i < q; i++) {
        que[i].l = lower_bound(vals.begin(),
        vals.end(), que[i].l) - vals.begin();
        que[i].r = lower_bound(vals.begin(),
        vals.end(), que[i].r) - vals.begin();   
    }
    sort(seg, seg + n);
    int l = vals.size(), maxr = -1;
    for (int i = 0, j = 0; i < l; i++) {
        while (j < n && seg[j].l <= i) {
            cmax(maxr, seg[j].r); j++;
        }
        nxt[0][i] = max(maxr, i);
    }
    for (int b = 1; b < LG; b++)
        for (int i = 0; i < l; i++)
            nxt[b][i] = nxt[b - 1][nxt[b - 1][i]];
    for (int i = 0; i < l; i++) {
        int x = i, y = k;
        for (int b = LG - 1; ~b; b--)
            if (y & (1 << b)) x = nxt[b][x];
        jump[i] = x;
    }
    for (int i = 0; i < l; i++)
        rmq[0][i] = vals[jump[i]] - vals[i];
    for (int b = 1; b < LG; b++)
        for (int i = 0; i + (1 << b) <= l; i++)
            rmq[b][i] = max(rmq[b - 1][i],
            rmq[b - 1][i + (1 << (b - 1))]);
    for (int i = 0; i < q; i++) {
        int l = que[i].l, r = que[i].r;
        int res = min(vals[r],
        vals[jump[l]]) - vals[l];
        if (jump[l] >= r) {
            cout << res << '\n'; continue;
        }
        int lo = l, hi = r, pos = r;
        while (lo <= hi) {
            int mi = (lo + hi) / 2;
            if (jump[mi] <= r) {
                pos = mi; lo = mi + 1;
            }
            else hi = mi - 1;
        }
        cmax(res, query(l, pos));
        if (pos < r)
            cmax(res, vals[r] - vals[pos + 1]);
        cout << res << '\n';
    }
}