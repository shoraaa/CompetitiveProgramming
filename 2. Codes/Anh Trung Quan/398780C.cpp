#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 5e4 + 5;
vector<int> adj[N];
string s;
int n;
ull base = 31, pw[N];
struct Centroid {
  int siz[N], vis[N]; 
  ull up[N], down[N];
  int len, root; vector<int> nxt[N];
  int size(int u, int p = -1) {
    siz[u] = 1;
    for (int v : adj[u]) if (v != p && !vis[v])
      siz[u] += size(v, u);
    return siz[u];
  }
  int find(int u, int s, int p = -1) {
    for (int v : adj[u]) if (v != p && !vis[v] && siz[v] > s)
      return find(v, s, u);
    return u;
  }
  void build(int u = 0, int p = -1) {
    u = find(u, size(u) / 2);
    if (p != -1) nxt[p].emplace_back(u);
    else root = u;
    vis[u] = 1; 
    for (int v : adj[u]) if (!vis[v])
      build(v, u);
  }
  set<ull> st;
  int get(int u, int p = -1, int d = 2) {
    down[d] = down[d-1] * base + (s[u] - 'a' + 1);
    up[d] = up[d-1] + pw[d-1] * (s[u] - 'a' + 1);
    if (d > len) return 0;
    if (d > len / 2) {
      int mid = d * 2 - len;
      if (up[mid] == down[mid] && st.count(down[d] - down[mid] * pw[d - mid]))
        return 1; 
    }
    for (int v : adj[u]) if (v != p && !vis[v])
      if (get(v, u, d + 1)) return 1;
    return 0;
  }
  void update(int u, int p = -1, int d = 1, ull val = 0) {
    if (d > (len - 1) / 2) return;
    val = val * base + s[u] - 'a' + 1;
    st.insert(val);
    for (int v : adj[u]) if (v != p && !vis[v])
      update(v, u, d + 1, val);
  }
  int solve(int u) {
    vis[u] = 1;
    down[1] = up[1] = s[u] - 'a' + 1;
    st.clear(); st.insert(0ULL);
    for (int v : adj[u]) if (!vis[v]) {
      if (get(v)) return 1;
      update(v);
    }
    st.clear(); st.insert(0ULL);
    reverse(adj[u].begin(), adj[u].end());
    for (int v : adj[u]) if (!vis[v]) {
      if (get(v)) return 1;
      update(v);
    }
    for (int v : nxt[u]) if (!vis[v]) 
      if (solve(v)) return 1;
    return 0;
  } 
  int check(int len) {
    this->len = len; 
    memset(vis, 0, sizeof(vis));
    return solve(root);
  }
} ct;
int get(vector<int>& len) {
  int lo = 0, hi = len.size() - 1, mid, ans = 1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (ct.check(len[mid]))
      ans = len[mid], lo = mid + 1;
    else
      hi = mid - 1;
  }
  return ans;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i)
    pw[i] = pw[i-1] * base;
  ct.build();
  vector<int> odd, even;
  for (int i = 1; i <= n; i += 2)
    odd.emplace_back(i);
  for (int i = 2; i <= n; i += 2)
    even.emplace_back(i);
  cout << max(get(odd), get(even));
}

