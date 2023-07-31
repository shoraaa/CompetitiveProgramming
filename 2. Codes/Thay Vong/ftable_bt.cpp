#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const int N = 505;
const ll INF = 1e18;
int n , m;
ll a[N][N], ori[N][N];
vector<ll> tmp;
ll sub2(int s, int t){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = ori[i][j];
    for (int i = s; i < n; i+=2)
        for (int j = t; j < m; j+=2){
            tmp.clear();
            for (int t = i; t <= i + 1; t++){
                for (int k = j; k <= j + 1; k++){
                    tmp.pb(a[t][k]);
                }
            }
            sort(tmp.begin(), tmp.end());
            ll med = tmp[1];
            med = -med;
            for (int t = i; t <= i + 1; t++){
                for (int k = j; k <= j + 1; k++){
                    a[t][k] += med;
                }
            }
        }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            ans += abs(a[i][j]);
        }
    return ans;
}
ll sub(int mask){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = ori[i][j];
    ll ans = INF;
    ll prev = 0;
    int tm = 0;
    while (tm <= 500){
        tm++;
        int cnt = -1;
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++){
                ++cnt;
                if (!(mask & (1 << cnt))) continue;
                tmp.clear();
                for (int t = i; t <= i + 1; t++){
                    for (int k = j; k <= j + 1; k++){
                        tmp.pb(a[t][k]);
                    }
                }
                sort(tmp.begin(), tmp.end());
                ll med = tmp[1];
                med = -med;
                for (int t = i; t <= i + 1; t++){
                    for (int k = j; k <= j + 1; k++){
                        a[t][k] += med;
                    }
                }
            }
        ll tmp = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++){
                tmp += abs(a[i][j]);
            }
        if (tmp == prev){ ans = min(ans, tmp); break;}
        prev = tmp;
    }
    return ans;
}
void sub1(){
    ll res = INF;
    for (int mask = 0; mask < (1 << ((n - 1) * (m - 1))); mask++)
        res = min(res, sub(mask));
    cout << res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("ftable.inp", "r", stdin);
    //freopen("ftable.out", "w", stdout);
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j], ori[i][j] = a[i][j];
    if ((n - 1) * (m - 1) <= 20){
        sub1(); return 0;
    }
    int tm = 0;
    ll res = INF;
    ll prev = 0;
    while (tm <= 500){
        tm++;
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++){
                tmp.clear();
                for (int t = i; t <= i + 1; t++){
                    for (int k = j; k <= j + 1; k++){
                        tmp.pb(a[t][k]);
                    }
                }
                sort(tmp.begin(), tmp.end());
                ll med = tmp[1];
                med = -med;
                for (int t = i; t <= i + 1; t++){
                    for (int k = j; k <= j + 1; k++){
                        a[t][k] += med;
                    }
                }
            }
        ll tmp = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++){
                tmp += abs(a[i][j]);
            }
        if (tmp == prev){ res = min(res, tmp); break;}
        prev = tmp;
    }

    res = min(res, sub2(1, 1));
    res = min(res, sub2(1, 2));
    res = min(res, sub2(2, 1));
    res = min(res, sub2(2, 2));
    cout << res;
}
/*
3 4
-5 -5 -5 -5
-5 -5 -5 -5
-3 -3 -3 -3
*/
/*
2 3
-4 0 4
-1 -2 3
*/
