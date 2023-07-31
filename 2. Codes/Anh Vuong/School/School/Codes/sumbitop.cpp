#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n; ll cnt[2];
    vector <int> a(n);
    ll sumand = 0, sumor = 0, sumxor = 0;
    for (int &x : a) cin >> x;
    for (int p = 20; ~p; p--){
        cnt[0] = cnt[1] = 0;
        for (int x : a) cnt[x >> p & 1]++;
        sumand += cnt[1] * (cnt[1] - 1) / 2 * (1ll << p);
        sumor += (cnt[1] * (cnt[1] - 1) / 2 + cnt[0] * cnt[1]) * (1ll << p);
        sumxor += cnt[0] * cnt[1] * (1ll << p);
    }
    cout << sumand << '\n' << sumor << '\n' << sumxor << '\n';
}