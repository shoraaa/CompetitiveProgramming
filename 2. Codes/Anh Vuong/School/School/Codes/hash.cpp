#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e15 + 37;
const int B = 127;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; string s[3]; vector <ll> v;
    cin >> n >> s[0] >> s[1] >> s[2];
    ll res = LLONG_MAX, pw = 1;
    for (int i = n / 2; i < n; i++) pw *= 3;
    for (int i = 0; i < pw; i++) {
        int x = i; ll hs = 0;
        for (int j = n / 2; j < n; j++) {
            hs = (hs * B + s[x % 3][j]) % MOD; x /= 3;
        }
        v.push_back(hs);
    }
    sort(v.begin(), v.end()); pw = 1;
    for (int i = 0; i < n / 2; i++) pw *= 3;
    for (int i = 0; i < pw; i++) {
        int x = i; ll hs = 0;
        for (int j = 0; j < n / 2; j++) {
            hs = (hs * B + s[x % 3][j]) % MOD; x /= 3;
        }
        for (int j = n / 2; j < n; j++)
            hs = hs * B % MOD;
        res = min(res, (hs + v.front()) % MOD);
        auto it = lower_bound(v.begin(), v.end(), MOD - hs);
        if (it != v.end())
            res = min(res, (hs + *it) % MOD);
    }
    cout << res << '\n';
}