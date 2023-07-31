#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
using ii = pair <int, int>;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector <ii> a(n);
    for (ii &sol : a)
        cin >> sol.fi >> sol.se;
    sort(a.begin(), a.end(),
    [&](ii p, ii q){
        return p.fi - p.se > q.fi - q.se;
    });
    long long res = 0; int last = 0;
    for (int i = 0; i < n; i++){
        if (last < a[i].fi){
            res += a[i].fi - last;
            last = a[i].fi;
        }
        last -= a[i].se;
    }
    cout << res << '\n';
}