#include <bits/stdc++.h>
using namespace std;

#define ub upper_bound
#define sqr(x) (x) * (x)
#define fi first
#define se second
using ll = long long;
using point = pair <ll, ll>;
using tll = tuple <ll, ll, int>;

const int N = 2e5 + 5;
int bit[N], id[N], ans[N], n, q;
point pt[N], cen[2]; tll que[N];

ll sdis(point a, point b){
    return sqr(a.fi - b.fi) + sqr(a.se - b.se);
}

void update(int i, int t){
    for (; i <= n; i += i & -i) bit[i] += t;
}

int query(int i){
    int res = 0;
    for (; i > 0; i -= i & -i) res += bit[i];
    return res;
}

int main(){
    freopen("nuclear.inp", "r", stdin);
    freopen("nuclear.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n; ll rad[2];
    for (int i = 1; i <= n; i++)
        cin >> pt[i].fi >> pt[i].se;
    for (int i = 0; i < 2; i++)
        cin >> cen[i].fi >> cen[i].se;
    cin >> q;
    for (int i = 1; i <= q; i++){
        cin >> rad[0] >> rad[1];
        que[i] = make_tuple(rad[0], rad[1], i);
    }
    sort(que + 1, que + q + 1);
    for (int i = 1; i <= n; i++){
        id[i] = i; bit[i]++;
        int j = i + (i & -i);
        if (j <= n) bit[j] += bit[i];
    }
    sort(pt + 1, pt + n + 1, [&](point x, point y){
        return sdis(x, cen[1]) < sdis(y, cen[1]);
    });
    sort(id + 1, id + n + 1, [&](int x, int y){
        return sdis(pt[x], cen[0]) < sdis(pt[y], cen[0]);
    });
    for (int i = 1, j = 0; i <= q; i++){
        int idq; tie(rad[0], rad[1], idq) = que[i];
        while (j < n && sdis(pt[id[j + 1]], cen[0]) <= sqr(rad[0])){
            j++; update(id[j], -1);
        }
        int k = ub(pt + 1, pt + n + 1,
        point(cen[1].fi, cen[1].se + rad[1]),
        [&](point x, point y){
            return sdis(x, cen[1]) < sdis(y, cen[1]);
        }) - pt - 1;
        ans[idq] = j + query(k);
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    
}
