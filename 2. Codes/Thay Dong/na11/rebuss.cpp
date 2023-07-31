#include<bits/stdc++.h>
using namespace std;
using ll = long long;

string a, b, c;
int last_a, last_b, last_c;
const int M = 1e9 + 7;
void add(int& x, const int y) {
  x += y; if (x >= M) x -= M;
}

int low(const string& s, int p, int last) {
  if (s[p] == '*') return p == last ? 1 : 0;
  return s[p] - '0';
}
int high(const string& s, int p) {
  if (s[p] == '*') return 9;
  return s[p] - '0';
}

int dp[55][5];
int call(int p, int rem) {
  if (p == a.size()) return rem == 0;
  if (~dp[p][rem]) return dp[p][rem];
  int res = 0;
  for (int i = low(a, p, last_a); i <= high(a, p); ++i) 
    for (int j = low(b, p, last_b); j <= high(b, p); ++j)
      for (int k = low(c, p, last_c); k <= high(c, p); ++k) {
        if ((i + j + rem) % 10 == k) add(res, call(p + 1, (i + j + rem) / 10));
      } 
  return dp[p][rem] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> a >> b >> c;
  reverse(a.begin(), a.end()); 
  reverse(b.begin(), b.end());
  reverse(c.begin(), c.end());
  int mx = max({a.size(), b.size(), c.size()});
  last_a = a.size() - 1, last_b = b.size() - 1, last_c = c.size() - 1;
  while (a.size() < mx) a += '0';
  while (b.size() < mx) b += '0';
  while (c.size() < mx) c += '0';
  memset(dp, -1, sizeof(dp));
  cout << call(0, 0);
	return 0;
}

