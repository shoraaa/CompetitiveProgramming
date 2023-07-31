#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
ll a[N], f[N], w[N];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T, H; cin >> T >> H;
  for (int i = 1; i <= H; ++i) cin >> w[i];
  a[1] = f[1] = w[1];
  for (int i = 2; i <= H; ++i) {
    a[i] = w[i] - a[1];
    for (int d = 2; d * d <= i; ++d) if (i % d == 0) {
      a[i] -= a[d];
      if (d * d != i) a[i] -= a[i / d];
    }
    f[i] = f[i - 1] + a[i];
  }
  while (T--) {
    cin >> n >> m;
    int lim = min(n, m); ll res = 0;
    for (int i = 1; i <= lim;) {
    	int la = n / (n / i), lb = m / (m / i);
    	if (la <= lb) {
    	  res += (f[la] - f[i - 1]) * (n / i) * (m / i);
    	  i = la + 1;
    	} else {
    	  res += (f[lb] - f[i - 1]) * (n / i) * (m / i);
    	  i = lb + 1;
    	}
    }
    cout << res << '\n';
  }

	return 0;
}

