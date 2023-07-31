#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1009, M = 998244353;
int n, m, a[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> c;
  for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) c.emplace_back(a[i]^a[j]);
  sort(c.rbegin(), c.rend()); 
  //for (int x : c) cerr << x << ' '; cerr << '\n';
  //cerr << c[m-1] << ' ' << bitset<10>(c[m-1]);
  int res = 0;
  for (int i = 0; i < m; ++i) {
    res += c[i];
    if (res >= M) res -= M;
  }
  cout << res;
	return 0;
}


