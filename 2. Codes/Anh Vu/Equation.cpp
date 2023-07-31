#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 500;
int cnt[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  ll L, R; cin >> L >> R;
  ll LIM = max(abs(L + 1), abs(R + 1)), LW = min(abs(R + 1), abs(L + 1));
  for (ll i = 2; i * i <= LIM; ++i) 
    for (ll j = max(i * i, (LW + i - 1) / i * i); j <= LIM; j += i) cnt[j - LW]++;
  ll res = 0;
  for (ll S = L + 1; S <= R + 1; ++S) {
    if (S == 0) return cout << -1, 0;
    if (S == 1) res += 2;
    else if (S == -1) res += 1;
    else {
      res += (cnt[abs(S) - LW] + 1) * 2;
      if (S < 0) {
        ll sq = sqrt(abs(S));
        if (sq * sq == abs(S)) res--;
      }
    }
  }
  cout << res;
	return 0;
}

