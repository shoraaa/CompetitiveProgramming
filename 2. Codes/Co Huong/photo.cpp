#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5;
vector<int> pr; int lp[N+1];
vector<pair<int, int>> fac[N+1], delta[N+1];
vector<pair<int, int>> dif(vector<pair<int, int>>& a, vector<pair<int, int>>& b) {
  vector<pair<int, int>> res;
  int n = a.size(), m = b.size();
  int i = 0, j = 0;
  while (i < n && j < m) {
    while (i < n && a[i].first < b[j].first) res.emplace_back(a[i]), i++;
    while (j < m && b[j].first < a[i].first) res.emplace_back(b[j]), j++;
    if (i < n && j < m && a[i].first == b[j].first)
      res.emplace_back(a[i].first, a[i].second - b[j].second), i++, j++;
  }
  while (i < n) res.emplace_back(a[i]), i++;
  while (j < m) res.emplace_back(b[j]), j++;
  vector<pair<int, int>> ans;
  for (auto& p : res) if (p.second) ans.emplace_back(p);
  return ans;
}
int rev(int x) {
  int res = 0;
  while (x) res = res * 10 + x % 10, x /= 10;
  return res;
}
int n, m, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n; cin >> n >> m >> k;
  for (int i = 2; i < N; ++i) {
    if (!lp[i]) pr.emplace_back(i), lp[i] = i;
    for (int p : pr) {
      if (p > lp[i] || i * p > N) break;;
      lp[i * p] = p;
    }
    int val = i;
    while (val > 1) {
      int x = lp[val], c = 0;
      while (val % x == 0) val /= x, c++;
      fac[i].emplace_back(x, c);
    }
  }
  for (int i = 1; i <= max(n, m); ++i)
    delta[i] = dif(fac[i], fac[rev(i)]);
  map<vector<pair<int, int>>, int> cnt;
  for (int y = 1; y <= m; ++y) {
    for (auto& p : delta[y]) cerr << p.first << ',' << p.second << ' ';
    cerr << '\n';
  }
  for (int y = 1; y <= m; ++y) cnt[delta[y]]++;
  int cur = 0, x, y, flag = 0;
  for (x = 1; x <= n; ++x) {
    cur += cnt[delta[x]];
    if (cur >= k) { flag = 1; break };
  }
  if (!flag) return cout << -1, 0;
  cnt.clear(); cur = 0;
  for (int i = 1; i <= x; ++i) cnt[delta[i]]++;
  for (y = 1; y <= m; ++y) {
    cur += cnt[delta[y]];
    if (cur >= k) break;
  }
  cout << x << ' ' << y;
	return 0;
}

