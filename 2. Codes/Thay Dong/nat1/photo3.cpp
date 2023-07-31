#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005;
int n, m, k;
vector<pair<int, int>> seq;
#define fi first
#define se second

int cost(int i, int j) {
  if (i > j) return 0;
  return (j - i + 1) * (j - i + 1);
}
// alien trick - wqs binary search
pair<int, int> dp[N];
pair<int, int> check(int m) {
  dp[seq.size() - 1] = {cost(seq.back().fi, seq.back().se) + m, 1};
  for (int i = seq.size() - 1; ~i; --i) {
    dp[i] = {cost(seq[i].fi, seq.back().se) + m, 1};
    for (int j = i + 1; j < seq.size(); ++j) {
      dp[i] = min(dp[i], 
                 {dp[j].fi + cost(seq[i].fi, seq[j - 1].se) - cost(seq[j].fi, seq[j - 1].se) + m, 
                  dp[j].se + 1});
    }
  }
  return dp[0];
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 0, x, y; i < n; ++i)
    cin >> x >> y, 
    seq.emplace_back(min(x, y), max(x, y));
  sort(seq.begin(), seq.end());
  vector<pair<int, int>> nxt;
  int max_r = -1;
  for (auto& p : seq) {
    int l, r; tie(l, r) = p;
    if (max_r >= r) continue;
    nxt.emplace_back(p); max_r = r;
  }
  seq.swap(nxt);

  int lo = 0, hi = 1e9, mid, ans = -1;
  while (lo <= hi) {
    int mid = lo + hi >> 1;
    auto p = check(mid);
    if (p.se <= k)
      ans = p.fi - p.se * mid,
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans;
  
	return 0;
}

