#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 500 + 5;
string s[N];
int n, m;
vector<int> lside;
int vis[N * N], match[N * N];
vector<int> G[N * N];
void dfs(int u, int b) {
  if (!b) lside.emplace_back(u);
  for (int v : G[u]) if (!vis[v]) 
    vis[v] = 1, dfs(v, !b);
}
int find_path(int u) {
  vis[u] = 1;
  for (int v : G[u]) if (!~match[v])
    return match[v] = u, 1;
  for (int v : G[u]) if (!vis[match[v]] && find_path(match[v]))
    return match[v] = u, 1;
  return 0;
}
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int inside(int r, int c) {
  return 0 <= r && r < n && 0 <= c && c < m;
}
int visited[N][N];
void existed_dfs(int r, int c) {
  for (int d = 0; d < 4; ++d) if (!visited[r + dr[d]][c + dc[d]] && inside(r + dr[d], c + dc[d])) {
    visited[r + dr[d]][c + dc[d]] = 1; 
    if (s[r + dr[d]][c + dc[d]] == 'L') 
      existed_dfs(r + dr[d], c + dc[d]);
    else s[r + dr[d]][c + dc[d]] = 'W';
  }
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> s[i];
  int existed = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) 
    if (s[i][j] == 'L' && !visited[i][j])
      existed++, visited[i][j] = 1, existed_dfs(i, j);

  vector<pair<int, int>> pos;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    if (s[i][j] == 'C') pos.emplace_back(i, j);
    
  for (int i = 0; i < pos.size(); ++i) {
    int r = pos[i].first, c = pos[i].second;
    for (int j = i+1; j < pos.size(); ++j) 
      if (abs(r - pos[j].first) + abs(c - pos[j].second) == 1)
        G[i].emplace_back(j), G[j].emplace_back(i);
  }
  for (int i = 0; i < pos.size(); ++i)
    if (!vis[i]) vis[i] = 1, dfs(i, 0);
  memset(match, -1, sizeof(match));
  int res = 0;
  for (int u : lside) {
    memset(vis, 0, sizeof(vis));
    res += find_path(u);
  }
  cout << pos.size() - res + existed;
	return 0;
}

