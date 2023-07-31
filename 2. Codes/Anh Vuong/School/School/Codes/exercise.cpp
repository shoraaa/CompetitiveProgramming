#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
using ll = long long;
using ii = pair <ll, ll>;

const int N = 505;
int sz[N]; ii a[N][N], b[N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n; ll res = 0;
    auto cmp = [&](ii p, ii q){
        return p.fi * q.se < p.se * q.fi;
    };
    for (int i = 1; i <= n; i++) cin >> sz[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= sz[i]; j++)
            cin >> a[i][j].fi;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= sz[i]; j++)
            cin >> a[i][j].se;
    for (int i = 1; i <= n; i++){
        ll sump = 0, sumw = 0;
        sort(a[i] + 1, a[i] + sz[i] + 1, cmp);
        for (int j = 1; j <= sz[i]; j++){
            sump += a[i][j].fi;
            sumw += a[i][j].se;
            res += sump * a[i][j].se;
        }
        b[i] = {sump, sumw};
    }
    ll sump = 0;
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; i++){
        res += sump * b[i].se;
        sump += b[i].fi;
    }
    cout << res << '\n';
}