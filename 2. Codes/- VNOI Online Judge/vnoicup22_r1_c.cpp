#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e6 + 5;
const int M = 1e9 + 7, B = 31;
int sum(int x, int y) {
  x += y; if (x >= M) x -= M; return x;
}
int mul(ll x, ll y) {
  return x * y % M;
}
pair<int, ull> pw[N];
struct S {
  string s;
  vector<pair<int, ull>> pre, suf;
  int i;
  bool operator < (const S& v) {
    return s.size() > v.s.size();
  }
  pair<int, ull> calc() {
    pre.resize(s.size()), suf.resize(s.size());
    pre[0].first = pre[0].second = s[0] - 'a' + 1;
    for (int i = 1; i < s.size(); ++i)
      pre[i].first = sum(mul(pre[i-1].first, B), s[i] - 'a' + 1),
      pre[i].second = pre[i-1].second * B + s[i]-'a'+1;
    suf.back().first = suf.back().second = s.back() - 'a' + 1;
    for (int i = s.size() - 2; i >= 0; --i)
      suf[i].first = sum(mul((s[i]-'a'+1), pw[s.size()-i-1].first), suf[i + 1].first),
      suf[i].second = (s[i]-'a'+1) * pw[s.size()-i-1].second + suf[i + 1].second;
    return suf[0];
  }
	pair<int, ull> insert(int i) {
		return {sum(mul(pre[i].first, pw[s.size()-i].first), suf[i].first),
										pre[i].second * pw[s.size()-i].second+suf[i].second};
	}
} a[N];
int res[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i].s, a[i].i = i;
	sort(a, a + n);
	pw[0].first = pw[0].second = 1;
	for (int i = 1; i < N; ++i)
		pw[i].first = mul(pw[i-1].first, B),
		pw[i].second = pw[i-1].second * B;
	map<pair<int, ull>, int> dp;
	for (int i = 0; i < n; ++i) {
		auto h = a[i].calc();
		if (dp[h]) {
			res[a[i].i] = dp[h];
			continue;
		}
		dp[h] = 1e9;
		for (int j = 0; j < a[i].s.size(); ++j) 
			dp[h] = min(dp[h], dp[a[i].insert(j)] + 1);
		assert(dp[h] != int(1e9));
		res[a[i].i] = dp[h];
	}
	for (int i = 0; i < n; ++i)
		cout << res[i] << '\n';
	return 0;
}

