#include <bits/stdc++.h>
#define bit(s,i) ((s >> i) & 1)

using namespace std;

int f[35];

int cal(int x,int lim) {
    if (lim < 0) return 0;
    int tplt = 0;
    lim++;
    int pre = -1;
    for (int i = 0 ; i <= 30 ; ++i) {
        if (pre < 0) f[i] = 1;
        else f[i] = f[pre] << (i - pre - 1);
        if (bit(x , i)) pre = i;
    }
    for (int i = 30 ; i >= 0 ; --i)
    if (bit(x , i)) {
        tplt += f[i] * (lim >> (i + 1));
        lim = min(1 << i , lim % (1 << (i + 1)));
    }
    return tplt + (lim > 0);
}

int main() {
    freopen("andcut.inp","r",stdin);
    freopen("andcut.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n , m , q , x , y , u , v;
    cin >> n >> m >> q;
    while (q--) {
        cin >> u >> v >> x >> y;
        cout << cal(v , x) - cal(v , u - 1) + (u && (u & v) == 0 && ((u - 1) & v) == 0)
            + cal(u , y) - cal(u , v - 1) + (v && (u & v) == 0 && ((v - 1) & u) == 0)
            - ((u & v) == 0) << '\n';
    }
}
