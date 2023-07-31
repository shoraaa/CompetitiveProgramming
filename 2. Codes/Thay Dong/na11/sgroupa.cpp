#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 3e6 + 5;
int lp[M], a[N], lef[M], rig[M];
vector<int> vert[2], adj[N];
int mn[2], vis[N];
int n, flag;

void dfs(int u, int c) {
  if (vis[u]) {
    if (vis[u] != c+1) flag = 1;
    return;
  }
  vis[u] = c+1; vert[c].emplace_back(u); mn[c] = min(mn[c], u);
  for (int v : adj[u]) dfs(v, !c);
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  
  for (int i = 2; i * i < M; ++i) if (!lp[i])
    for (int j = i * i; j < M; j += i) lp[j] = i;
  for (int i = 2; i < M; ++i) if (!lp[i]) lp[i] = i;
  
  while (T--) {
    cin >> n;
    memset(lef, -1, sizeof(lef)); 
    memset(rig, -1, sizeof(rig));
    
    vector<int> res;
    int m = 0; flag = 0;
    for (int i = 0; i < n; ++i) {
      cin >> a[i], m = max(m, a[i]); assert(a[i] != 0);
      while (a[i] > 1) {
        int x = lp[a[i]];
        while (a[i] % x == 0) a[i] /= x;
        
        if (lef[x] == -1) lef[x] = i;
        else if (rig[x] == -1) rig[x] = i;
        else flag = 1;
        
      }
    }
    if (flag) {
      cout << -1 << '\n'; continue;
    }
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int x = 2; x <= m; ++x) if (~lef[x] && ~rig[x]) 
      adj[lef[x]].emplace_back(rig[x]), 
      adj[rig[x]].emplace_back(lef[x]);
    
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) if (!vis[i]) {
      vert[0].clear(), vert[1].clear(); mn[0] = 1e9, mn[1] = 1e9;
      dfs(i, 0);
      
      if (flag) break;
      
      int ans = (vert[1].size() > vert[0].size()) || (vert[1].size() == vert[0].size() && mn[1] < mn[0]);
      for (int v : vert[ans]) res.emplace_back(v); 
    }
    
    if (flag) {
      cout << -1 << '\n'; continue;
    }
    
    sort(res.begin(), res.end());
    cout << res.size() << ' ';
    for (int v : res) cout << v + 1 << ' ';
    cout << '\n';
  }
	return 0;
}

