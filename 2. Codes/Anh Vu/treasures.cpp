#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 300 + 5;
struct C {
  int i, j;
  C(int i, int j): i(i), j(j) {}
};
int a[N][N], dp[N][N], cur[N][N], vis[N][N];
vector<C> pos[N * N];
int n, m, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    cin >> a[i][j], a[i][j]--, 
    pos[a[i][j]].emplace_back(i, j);
  memset(dp, 0x3f, sizeof(dp));
  for (auto& p : pos[0]) 
    dp[p.i][p.j] = p.i + p.j;
  queue<pair<C, int>> q;
  for (int i = 1; i < k; ++i) {
    if (pos[i].size() <= N && pos[i-1].size() <= N) {
      for (auto& p1 : pos[i]) for (auto& p2 : pos[i-1])
        dp[p1.i][p1.j] = min(dp[p1.i][p1.j], 
                             dp[p2.i][p2.j] + abs(p1.i-p2.i) + abs(p1.j-p2.j));
    } else {
      sort(pos[i-1].begin(), pos[i-1].end(), [&](const C& u, const C& v) {
        return dp[u.i][u.j] < dp[v.i][v.j];
      });
      q.emplace(pos[i-1][0], dp[pos[i-1][0].i][pos[i-1][0].j]);
      int nxt = 1, last = pos[i-1].size(), pre = i-1, first = q.front().second;
      while (nxt < last && dp[pos[pre][nxt].i][pos[pre][nxt].j] == first)
        q.emplace(pos[pre][nxt], first), nxt++;
      memset(cur, 0, sizeof(cur));
      memset(vis, 0, sizeof(vis));
      for (auto& p : pos[i])
        cur[p.i][p.j] = 1;
      while (!q.empty()) {
        auto p = q.front(); q.pop(); 
        int i = p.first.i, j = p.first.j, v = p.second;
        if (vis[i][j]) continue;
        vis[i][j] = 1;
        if (cur[i][j]) dp[i][j] = min(dp[i][j], v);
        if (i < n-1) q.emplace(C(i+1, j), v+1);
        if (i > 0) q.emplace(C(i-1, j), v+1);
        if (j < m-1) q.emplace(C(i, j+1), v+1);
        if (j > 0) q.emplace(C(i, j-1), v+1);   
        while (nxt < last && dp[pos[pre][nxt].i][pos[pre][nxt].j] == v+1)
          q.emplace(pos[pre][nxt], v+1), nxt++;
      }
    }
  }
  cout << dp[pos[k-1][0].i][pos[k-1][0].j];
	return 0;
}

