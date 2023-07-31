#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 205;
vector<int> adj[N];
int a[N][N], b[N][N];

int n;

int idx[N], siz[N], id = 0;
void dfs1(int u) {
  idx[u] = id; siz[id]++;
  for (int v : adj[u]) if (!~idx[v]) dfs1(v);
}

int cnt[2], col[N];
void dfs2(int u) {
  cnt[col[u]] += siz[u];
  for (int v : adj[u]) {
    if (!~col[v]) col[v] = col[u] ^ 1, dfs2(v);
    else if (col[u] == col[v]) cout << -1, exit(0);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) 
      cin >> a[i][j];
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> b[i][j];
      if (b[i][j] == 0 && a[i][j] != 0) return cout << -1, 0;
      if (b[i][j] != 0 && a[i][j] == 0) return cout << -1, 0;
      
      if (b[i][j] == 0 || a[i][j] != b[i][j]) continue;
      
      adj[i].emplace_back(j + n);
      adj[j + n].emplace_back(i);
    }
  }

  memset(idx, -1, sizeof(idx));
  for (int i = 0; i < n * 2; ++i) 
    if (!~idx[i]) dfs1(i), id++;
  for (int i = 0; i < id; ++i) adj[i].clear();
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (b[i][j] == 0 || a[i][j] == b[i][j]) continue;
      if (idx[i] == idx[j + n]) return cout << -1, 0;
      
      adj[idx[i]].emplace_back(idx[j + n]);
      adj[idx[j + n]].emplace_back(idx[i]);
    }
  }
  
  memset(col, -1, sizeof(col));
  int res = 0;
  for (int i = 0; i < id; ++i) if (!~col[i]) {
    col[i] = 0, cnt[0] = cnt[1] = 0;
    dfs2(i);
    res += min(cnt[0], cnt[1]);
  }
  cout << res;
	return 0;
}
