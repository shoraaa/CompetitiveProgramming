#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e6 + 5;
ull pw[N], b = 31;
string w[N], t;
int d[N];
int n, m, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> w[i];
  for (int i = 0; i < m; ++i)
    cin >> d[i];
  int g = d[0];
  for (int i = 1; i < m; ++i)
    g = __gcd(g, d[i]);
  for (int i = 0; i < n; ++i)
    g = __gcd(g, int(w[i].size()));
  vector<ull> cont;
  for (int i = 0; i < n; ++i) {
    ull cur = 0;
    for (int j = 0; j < w[i].size(); ++j) {
      cur *= b, cur += w[i][j] - 'a' + 1;
      if ((j + 1) % g == 0) cont.emplace_back(cur);
    }
  }
  sort(cont.begin(), cont.end());
  pw[0] = 1;
  for (int i = 1; i < N; ++i)
    pw[i] = pw[i-1] * b;
  cin >> q;  
  for (int i = 0; i < q; ++i) {
    cin >> t; n = t.size();
    if (n % g != 0) {
      cout << "No\n"; continue;
    }
    ull cur = 0; int len = 0;
    for (int i = n-1; ~i; --i) {
      cur += pw[len] * (t[i] - 'a' + 1), len++;
      if (binary_search(cont.begin(), cont.end(), cur)) 
        cur = 0, len = 0;
    }
    cout << (len == 0 ? "Yes\n" : "No\n");
  }
	return 0;
}

