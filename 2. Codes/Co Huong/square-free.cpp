#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = sqrt(1e9) + 5;
int lp[M+1]; vector<int> pr;
int cnt[int(1e7)+1], max_len = 0, max_val = 0;
void solve() {
  for (int p : pr) {
    int b = p*p;
    for (int i = b; i <= max_val; i += b) 
      cnt[i] = 1;
  }
  for (int i = 1; i <= max_val; ++i)
    cnt[i] = cnt[i-1] + !cnt[i];
}
int sqf(int x) {
   for (int p : pr) {
     if (p * p > x) break;
     if (x % (p * p) == 0) return 0;
   }
   return 1;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("square-free.inp", "r"))
    freopen("square-free.inp", "r", stdin),
    freopen("square-free.out", "w", stdout);
  for (int i = 2; i <= M; ++i) {
    if (!lp[i]) lp[i] = i, pr.emplace_back(i);
    for (int p : pr) {
      if (i * p > M || p > lp[i]) break;
      lp[i * p] = p;
    }
  }
  int n; cin >> n;
  vector<pair<int, int>> a(n);
  for (auto& p : a)
    cin >> p.first >> p.second,
    max_len = max(max_len, p.second - p.first),
    max_val = max(max_val, p.second);
  if (max_len <= 300) {
    for (auto& p : a) {
      int cnt = 0;
      for (int i = p.first; i <= p.second; ++i)
        cnt += sqf(i);
      cout << cnt << '\n';
    }
  } else {
    solve();
    for (auto& p : a) 
      cout << cnt[p.second] - cnt[p.first - 1] << '\n';
  }
	return 0;
}

