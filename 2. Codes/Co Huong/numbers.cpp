#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll dp[19][2][2][11][11][2];
vector<int> a, b;
ll call(int pos, int gr, int le, int pre, int prev, int nz) {
  if (pos == a.size()) return 1;
  if (dp[pos][gr][le][pre+1][prev+1][nz] != -1)
    return dp[pos][gr][le][pre+1][prev+1][nz];
  int lw = gr ? 0 : a[pos], up = le ? 9 : b[pos];
  ll res = 0;
  for (int d = lw; d <= up; ++d) 
    if (!nz || (d != pre && d != prev))
      res += call(pos + 1, gr | (d > lw), le | (d < up), d, nz ? pre : -1, nz | (d > 0));
  return dp[pos][gr][le][pre+1][prev+1][nz] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("numbers.in", "r"))
	  freopen("numbers.in", "r", stdin),
	  freopen("numbers.out", "w", stdout);
  ll A, B; cin >> A >> B;
  while (A) a.emplace_back(A % 10), A /= 10;
  while (B) b.emplace_back(B % 10), B /= 10;
  while (a.size() < b.size()) a.emplace_back(0);
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  memset(dp, -1, sizeof(dp));
  cout << call(0, 0, 0, -1, -1, 0);
	return 0;
}

