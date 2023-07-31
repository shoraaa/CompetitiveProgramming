
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<int> adj[N];
int n, m, q;

int cnt = 0;

struct BIT {
  vector<int> node; 
  vector<ll> val;
  void pre_add(int x) {
    node.emplace_back(-x);
  }
  void build() {
    sort(node.begin(), node.end());
    node.erase(unique(node.begin(), node.end()), node.end());
    val.resize(node.size());
  }
  void add(int x, int v) {  
    for (int i = upper_bound(node.begin(), node.end(), -x) - node.begin();
      i <= node.size(); i += i & -i) val[i - 1] += v;
    
  }
  ll get(int x) {
    ll res = 0; 
    for (int i = upper_bound(node.begin(), node.end(), -x) - node.begin();
      i; i -= i & -i) res += val[i - 1];
    return res;
  }  
} bit[N];
vector<BIT> bit2[N];

struct F {
  int t, u, c, s;
  bool operator < (const F& f) const {
    return t < f.t;
  }
} a[N];

struct Q {
  int d, v, i; 
  bool operator < (const Q& q) const {
    return d < q.d;
  }
} b[N];


int siz[N], par[N];

int Size(int u, int e) {
  siz[u] = 1;
  for (int v : adj[u]) if (v != e && !par[v])
    siz[u] += Size(v, u);
  return siz[u];
}
int find(int u, int e, int s) {
  for (int v : adj[u]) if (v != e && !par[v] && siz[v] * 2 > s)
    return find(v, u, s);
  return u;
}

int height[N], dis[17][N], dir[17][N];
//map<int, int> dis[N], dir[N];
void dfs(int u, int e, int c, int d, int dr) {
  dis[c][u] = d; dir[c][u] = dr;
  for (int v : adj[u]) if (v != e && !par[v])
    dfs(v, u, c, d + 1, dr);
}
void decompose(int u = 1, int e = 0, int h = 0) {
  u = find(u, e, Size(u, e));
  if (e == 0) par[u] = -1;
  else par[u] = e;
  height[u] = h;
  int dr = 0;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v == e || par[v]) continue;
    dfs(v, u, h, 1, dr++);
  }
  bit2[u].resize(dr);
  
  for (int v : adj[u]) if (!par[v]) 
    decompose(v, u, h + 1);
}

void pre_insert(int u, int s) {
  for (int p = u, h = height[p]; ~h; p = par[p], h--) {
    bit[p].pre_add(s - dis[h][u]);
    if (p != u) bit2[p][dir[h][u]].pre_add(s - dis[h][u]);
  }
}

void insert(int u, int s, int c) {
  for (int p = u, h = height[p]; ~h; p = par[p], h--) {
    bit[p].add(s - dis[h][u], c);
    if (p != u) bit2[p][dir[h][u]].add(s - dis[h][u], c);
  }
}

ll get(int u) {
  ll res = 0;
  for (int p = u, h = height[p]; ~h; p = par[p], h--) { 
    res += bit[p].get(dis[h][u]);
    if (p != u) res -= bit2[p][dir[h][u]].get(dis[h][u]);
  }
  return res;
}

ll ans[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("firework.inp", "r"))
    freopen("firework.inp", "r", stdin),
    freopen("firework.out", "w", stdout);
    
  cin >> n >> m >> q;
  
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < m; ++i)
    cin >> a[i].t >> a[i].u >> a[i].c >> a[i].s;
  for (int i = 0; i < q; ++i)
    cin >> b[i].d >> b[i].v, b[i].i = i;
  sort(a, a + m); sort(b, b + q);
  
  decompose(); 
   for (int i = 0, j = 0; i < q; ++i) 
     while (j < m && a[j].t <= b[i].d) pre_insert(a[j].u, a[j].s), j++;
  
   for (int c = 1; c <= n; ++c) {
     bit[c].build();
     for (int i = 0; i < bit2[c].size(); ++i) bit2[c][i].build();
   }
   
   for (int i = 0, j = 0; i < q; ++i) {
     while (j < m && a[j].t <= b[i].d) insert(a[j].u, a[j].s, a[j].c), j++;
     ans[b[i].i] = get(b[i].v);
   }

   for (int i = 0; i < q; ++i)
     cout << ans[i] << '\n';

	return 0;
}

