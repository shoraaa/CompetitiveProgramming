#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int a[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; string s(n, '.');
  ll res = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] > 0) s[i] = '(', res += a[i];
    else if (a[i] < 0) s[i] = ')', res -= a[i];
  }
  cerr << s << '\n';
  int cur = 0;
  priority_queue<pair<int, int>> used, skipped;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') cur++;
    else if (s[i] == ')') cur--, used.emplace(a[i], i);
    else skipped.emplace(a[i], i);
    if (cur < 0) {
      if (!used.empty() && (skipped.empty() || used.top().first > skipped.top().first)) {
        auto p = used.top(); used.pop();
        res += p.first; s[p.second] = '.'; skipped.emplace(p);
      } else {
        auto p = skipped.top(); skipped.pop();
        res += p.first; s[p.second] = '('; 
      }
      cur++;
    }
  }
  cerr << s << '\n';
  assert(cur >= 0); cur = 0; 
  while (!used.empty()) used.pop();
  while (!skipped.empty()) skipped.pop();
  for (int i = n-1; ~i; --i) {
    if (s[i] == ')') cur++;
    else if (s[i] == '(') cur--, used.emplace(-a[i], i);
    else skipped.emplace(-a[i], i);
    if (cur < 0) {
      if (!used.empty() && (skipped.empty() || used.top().first > skipped.top().first)) {
        auto p = used.top(); used.pop();
        res += p.first; s[p.second] = '.'; skipped.emplace(p);
      } else {
        auto p = skipped.top(); skipped.pop();
        res += p.first; s[p.second] = ')'; 
      }
      cur++;
    }
  }
  cerr <<s  << '\n';
  cout << res << '\n';
  

	return 0;
}

