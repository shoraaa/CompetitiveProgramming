#include <bits/stdc++.h>
using namespace std;

#define lmao laughing
#define all(v) (v).begin(), (v).end()
#define ub upper_bound
#define eb emplace_back

const int N = 2e5 + 5;
int a[N], tree[4 * N], lazy[4 * N];
vector <int> pos[N];

void lazy_down(int i, int lo, int hi){
    tree[i] += lazy[i];
    if (lo != hi){
        lazy[i * 2] += lazy[i];
        lazy[i * 2 + 1] += lazy[i];
    }
    lazy[i] = 0;
}

void update(int i, int lo, int hi,
            int l, int r, int val){
    lazy_down(i, lo, hi);
    if (l > r || lo > r || hi < l) return;
    if (lo >= l && hi <= r){
        tree[i] += val;
        if (lo != hi){
            lazy[i * 2] += val;
            lazy[i * 2 + 1] += val;
        }
        return;
    }
    int mi = (lo + hi) / 2;
    update(i * 2, lo, mi, l, r, val);
    update(i * 2 + 1, mi + 1, hi, l, r, val);
    tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
}

int query(int i, int lo, int hi, int l, int r){
    lazy_down(i, lo, hi);
    if (l > r || lo > r || hi < l) return 0;
    if (lo >= l && hi <= r) return tree[i];
    int mi = (lo + hi) / 2;
    return max(query(i * 2, lo, mi, l, r),
            query(i * 2 + 1, mi + 1, hi, l, r));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, res = 0; cin >> n;
    vector <int> cmp;
    for (int i = 1; i <= n; i++){
        cin >> a[i]; cmp.eb(a[i]);
    }
    sort(cmp.begin(), cmp.end());
    cmp.resize(unique(all(cmp)) - cmp.begin());
    for (int i = 1; i <= n; i++)
        a[i] = ub(all(cmp), a[i]) - cmp.begin();
    for (int i = 1; i <= n; i++) pos[i].eb(0);
    for (int i = 1; i <= n; i++){
        pos[a[i]].eb(i);
        int sz = pos[a[i]].size();
        if (sz > 2)
            update(1, 1, n, pos[a[i]][sz - 3] + 1,
                    pos[a[i]][sz - 2], 1);
        if (sz > 3)
            update(1, 1, n, pos[a[i]][sz - 4],
                    pos[a[i]][sz - 3], -1);
        res = max(res, query(1, 1, n, 1, n));
    }
    cout << res << '\n';
}