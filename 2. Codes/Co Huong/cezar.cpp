#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 5;
vector<int> adj[N];
int n, k;

struct SegmentTree {
  int n, v, sgn; ll res;
  vector<int> cnt; vector<ll> val;
  SegmentTree() = default;
  SegmentTree(int n): n(n), val(n*2), cnt(n*2) {}
  void get(int k, int l, int r) {
    if (l == r) {
      if (v <= cnt[k]) res += l * v, v = 0;
      else v -= cnt[k], res += val[k];
      return;
    }
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    if (v <= cnt[rc]) get(rc, m+1, r);
    else v -= cnt[rc], res += val[rc], get(lc, l, m);
  }
  void update(int k, int l, int r) {
    val[k] += v * sgn, cnt[k] += sgn;
    if (l == r) return void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    if (v <= m) update(lc, l, m);
    else update(rc, m+1, r);
  }
  void update(int v, int sgn) {
    this->v = v, this->sgn = sgn;
    update(1, 1, n);
  }
  ll get(int v) {
    this->v = v; res = 0;
    get(1, 1, n);
    return res;
  }
} st;

int sz[N]; ll dp[N];
void dfs1(int u, int p) {
  sz[u] = 1; 
  for (int v : adj[u]) if (v != p) {
    dfs1(v, u);
    sz[u] += sz[v];
    dp[u] += dp[v] + sz[v];
  }
  st.update(sz[u], 1);
}

ll res = 1e18;
void dfs2(int u, int p) {
  st.update(sz[u], -1);
  res = min(res, dp[u] - st.get(k));
  st.update(sz[u], 1);
  
  for (int v : adj[u]) if (v != p) {
    dp[u] -= dp[v] + sz[v];
    st.update(sz[u], -1); sz[u] -= sz[v]; st.update(sz[u], 1);
    st.update(sz[v], -1); sz[v] += sz[u]; st.update(sz[v], 1);
    dp[v] += dp[u] + sz[u];
    dfs2(v, u);
    dp[v] -= dp[u] + sz[u];
    st.update(sz[v], -1); sz[v] -= sz[u]; st.update(sz[v], 1);
    st.update(sz[u], -1); sz[u] += sz[v]; st.update(sz[u], 1);
    dp[u] += dp[v] + sz[v];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("cezar.inp", "r"))
    freopen("cezar.inp", "r", stdin),
    freopen("cezar.out", "w", stdout);
    
  cin >> n >> k; st = SegmentTree(n);
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs1(0, -1);
  dfs2(0, -1);
  cout << res << '\n';
	return 0;
}

