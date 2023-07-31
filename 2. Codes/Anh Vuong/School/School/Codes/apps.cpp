#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
using ii = pair <int, int>;

const int N = 1e5 + 5;
int dp[N]; ii a[505];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, c; cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> a[i].fi >> a[i].se;
    sort(a + 1, a + n + 1,
    [&](ii p, ii q){
        return p.se - max(p.fi, p.se) < 
                q.se - max(q.fi, q.se);
    });
    for (int i = 1; i <= n; i++){
        if (c < a[i].se) continue;
        for (int j = c; j >= a[i].se; j--)
            if (c - j + a[i].se >= max(a[i].fi, a[i].se))
                dp[j] = max(dp[j], dp[j - a[i].se] + 1);
    }
    cout << *max_element(dp, dp + N) << '\n';
}
