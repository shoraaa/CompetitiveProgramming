#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 10005;
vector<int> adj[N];
int n, m;

int vis[N], idx[N], color[N];
void dfs(int u) {
  vis[u] = 1; //cerr << u << ' ' << color[u] << '\n';
  for (int v : adj[u]) if (!vis[v]) {
    if (~color[v] && color[u] == color[v]) {
      cout << 0; exit(0);
    }
    color[v] = !color[u];
    dfs(v);
  }
}

void add(int u, int v) {
  adj[u].emplace_back(v);
  adj[v].emplace_back(u);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; int id = 0; 
  for (int i = 0; i < n; ++i) idx[i] = id++;
  for (int i = 0; i < m; ++i) idx[n+i] = id++;
  memset(color, -1, sizeof(color));
  int flag = 0;
  for (int i = 0, x; i < n; ++i) for (int j = 0; j < m; ++j) {
    cin >> x;
    if (x == 0) continue;
    if (x == 1) {
      if (~color[idx[i]] && color[idx[i]] != 0) return cout << 0, 0;
      if (~color[idx[n + j]] && color[idx[n + j]] != 0) return cout << 0, 0;
      color[idx[i]] = color[idx[n+j]] = 0;
    } else if (x == 2) {
      if (~color[idx[i]] && color[idx[i]] != 1) return cout << 0, 0;
      if (~color[idx[n + j]] && color[idx[n + j]] != 1) return cout << 0, 0;
      color[idx[i]] = color[idx[n+j]] = 1;
    } else if (x == 3) add(idx[i], idx[n+j]);
    
    if (x != 3) flag = 1;
  }

  int cnt = 0;
  for (int i = 0; i < id; ++i)
    if (!vis[i] && ~color[i]) dfs(i);
  for (int i = 0; i < id; ++i)
    if (!vis[i] && !~color[i]) color[i] = 0, dfs(i), cnt++;
  ll res = 1LL << cnt;
  if (!flag) res--;
  cout << res;
	return 0;
}
