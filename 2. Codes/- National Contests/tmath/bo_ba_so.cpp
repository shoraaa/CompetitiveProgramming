#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll p, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> p >> q;
  ll res = 0;
  for (ll a = 0; a <= p; ++a) for (ll b = 0, c = p-a; b <= p-a; ++b) {
    while (a+b+c > p || a*b*c > q) c--;
    res += c+1;
  }
  cout << res;
	return 0;
}

