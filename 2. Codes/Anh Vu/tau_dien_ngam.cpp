#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e2 + 5, C = 120, T = 60;
const int inf = 1e9;
struct AdjacentEdge {
  int v, w[2];
  AdjacentEdge(int v, int w): v(v) {
    this->w[0] = w - (w / T) * T;
    this->w[1] = w - ((w + T-1) / T) * T;
  }
};
vector<AdjacentEdge> adj[N];
int n;
array<int, C> call(int u, int p, int t) {
  array<int, C> cur;
  fill(cur.begin(), cur.end(), -inf);
  cur[0] = 0;
  for (auto& c : adj[u]) if (c.v != p) {
    array<int, C> nxt = call(c.v, u, t), dp;
    fill(dp.begin(), dp.end(), -inf);
    for (int r1 = 0; r1 <= C; ++r1) for (int r2 = 0; r2 <= C; ++r2) {
      for (int i = 0; i < 2; ++i) {
        int new_l = min(cur[r1], nxt[r2] + c.w[i]), new_r = max(r1, r2 + c.w[i]);
        if (max(abs(cur[r1] + nxt[r2] + c.w[i]), abs(r1 + r2 + c.w[i])) <= t)
          dp[new_r] = max(dp[new_r], new_l);
      }
    }
    cur.swap(dp); 
  }
  return cur;
}
int check(int t) {
  auto dp = call(0, -1, t);
  for (int r = 0; r <= t; ++r) 
    if (dp[r] >= -t) return 1;
  return 0;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	for (int c = 1;; ++c) {
    cin >> n; if (n == 0) break;
    for (int u = 0; u < n; ++u)
      adj[u].clear();
    for (int i = 0, u, v, w; i < n-1; ++i)
      cin >> u >> v >> w, u--, v--,
      adj[u].emplace_back(v, w),
      adj[v].emplace_back(u, w);
    int lo = 0, hi = C-1, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid))
        ans = mid, hi = mid - 1;
      else
        lo = mid + 1;
    }
    cout << "Case " << c << ": " << ans << '\n';
  }
	return 0;
}

