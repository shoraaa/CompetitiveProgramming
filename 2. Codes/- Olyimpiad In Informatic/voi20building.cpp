#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const int INF = 1e9;

struct Rectangle {
  int l, r, d, t;
} a[N];
int n;

map<int, vector<pair<int, int>>> dow, lef;
#define fi first
#define se second


vector<int> adj[N];
void add_edge(int u, int v) {
  adj[u].emplace_back(v);
  adj[v].emplace_back(u);
}

vector<pair<int, int>> bridges;

int t = 0;
int in[N], low[N], siz[N];
void dfs(int u, int p = 0) {
  in[u] = low[u] = ++t;
  siz[u] = 1;
  for (int v : adj[u]) {
    if (v == p) continue;
    
    if (in[v]) {
      low[u] = min(low[u], in[v]);
    } else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      siz[u] += siz[v];
    }
    
    if (low[v] > in[u]) {
      bridges.emplace_back(u, v);
    }
    
  }
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].l >> a[i].t >> a[i].r >> a[i].d;
    
    dow[a[i].d].emplace_back(a[i].l, i);
    lef[a[i].l].emplace_back(a[i].d, i);
    
  }
  
  for (auto& p : dow) {
    sort(p.se.begin(), p.se.end());
  }
  for (auto& p : lef) {
    sort(p.se.begin(), p.se.end());
  }
  
  for (int i = 1; i <= n; ++i) {
    
    auto vec = dow[a[i].t];
    int j = upper_bound(vec.begin(), vec.end(), make_pair(a[i].l, INF)) - vec.begin();
    
    if (j && a[vec[j - 1].se].r >= a[i].l) {
      add_edge(i, vec[j - 1].se);
    }
    
    while (j < vec.size()) {
      if (vec[j].fi > a[i].r) break;
      add_edge(i, vec[j].se);
      j++;
    }
    

    vec = lef[a[i].r];
    j = upper_bound(vec.begin(), vec.end(), make_pair(a[i].d, INF)) - vec.begin();
    
    if (j && a[vec[j - 1].se].t >= a[i].d) {
      add_edge(i, vec[j - 1].se);
    }
    
    while (j < vec.size()) {
      if (vec[j].fi > a[i].t) break;
      add_edge(i, vec[j].se);
      j++;
    }
    
  }
  
  for (int i = 1; i <= n; ++i) {
    sort(adj[i].begin(), adj[i].end());
    adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
  }
  
  int res = INF;
  
  for (int i = 1; i <= n; ++i) {
    if (!in[i]) {
      
      bridges.clear();
      dfs(i);
      for (auto& p : bridges) {
        int u, v; tie(u, v) = p;
        res = min(res, abs((siz[i] - siz[v]) - siz[v]));
      }
      
    }
  }
  
  if (res == INF) {
    cout << -1;
  } else {
    cout << res;
  }
	return 0;
}

