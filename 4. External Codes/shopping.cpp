#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 5;
using ll = long long;
#define int ll
int n, a[N], pre[N];
vector<pii> b;
ll ans, m, mx[N];

void cmax(ll &x, ll y){x = max(x, y);}
ll bs(ll tot, int id){
    if (!id) return 0;
    ll res = 0;
    int mid = 0, left = 0, right = tot;
    int md = 0;
    while (left <= right){
        mid = (left + right) / 2;
        ll tmp = pre[id] * mid + mx[id];
        bool nx = true;
        if (tmp > tot) nx = false;
        if (nx) md = mid, left = mid + 1;
        else right = mid - 1;
    }
    res = b[id].se * md * b[id].fi + bs(tot - b[id].se * md, id - 1);
    //if (id == n) cmax(res, bs(tot, id - 1));
    return res;
}



signed main(){
    //freopen("shopping.inp", "r", stdin);
    //freopen("shopping.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    b.eb(0, 0);
    for (int i = 1; i <= n; i++){
        if (a[i] != a[i - 1]) b.eb(a[i], 1);
        else b[b.size() - 1].se++;
    }
    int n = b.size() - 1;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + b[i].se;
    for (int i = 1; i <= n; i++)
        mx[i] = mx[i - 1] + pre[i - 1];
    cout << bs(m, n);
}
/*
3 7
2 3 8
*/
