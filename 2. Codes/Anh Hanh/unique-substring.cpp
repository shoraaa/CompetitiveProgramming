#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define fi first
#define se second
vector<int> suffix_array(string& s) {
  int n = s.size();
  vector<int> rank(n), pos(n); vector<pair<int, int>> val(n);
  iota(pos.begin(), pos.end(), 0); auto cmp = [&](int i, int j) { return val[i] < val[j]; };
  for (int i = 0; i < n; ++i) rank[i] = s[i] - 'a';
  for (int k = 0; (1 << k) < n; ++k) {
    for (int i = 0; i < n; ++i) {
      int p = i + (1 << k);
      val[i] = {rank[i], p < n ? rank[p] : -1};
    }
    sort(pos.begin(), pos.end(), cmp);
    rank[pos[0]] = 0;
    for (int i = 1, c = 0; i < n; ++i) {
      if (val[pos[i]] != val[pos[i-1]]) c++;
      rank[pos[i]] = c;
    }
  }
  return rank;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("unique-substring.inp", "r"))
    freopen("unique-substring.inp", "r", stdin),
    freopen("unique-substring.out", "w", stdout);
  string s; cin >> s; 
  vector<int> rank = suffix_array(s);
  int n = s.size();
  vector<int> p(n, 0);
  for (int i = 0; i < n; i++)
    p[rank[i]] = i;
  int k = 0;
  vector<int> lcp(n, 0);
  for (int i = 0; i < n; i++) {
    if (rank[i] == n - 1) {
      k = 0; continue;
    }
    int j = p[rank[i] + 1];
    while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
    lcp[rank[i]] = k;
    if (k) k--;
  }
  pair<int, int> res = {n + 1, -1};
  for (int i = 0; i < n; ++i) if (p[i] + max(i > 0 ? lcp[i - 1] : 0, lcp[i]) < n)
    res = min(res, {max(i > 0 ? lcp[i - 1] : 0, lcp[i]) + 1, i});
  cout << s.substr(p[res.se], res.fi);
	return 0;
}

