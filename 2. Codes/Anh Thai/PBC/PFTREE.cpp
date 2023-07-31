#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, C = 230, M = 1e9 + 7, M9 = 1e9;
vector<int> adj[N];
int n, m;

struct Query {
  int l, r, i;
  Query(int l, int r, int i): l(l), r(r), i(i) {}
  bool operator < (const Query& q) const {
    return make_pair(l / C, r) < make_pair(q.l / C, r);
  }
};
vector<Query> queries;

int t = 0;
int a[N], dep[N], cnt[N], max_d = 0;
void dfs(int u = 0, int p = -1) {
  int in = t++; a[in] = u;
  for (int v : adj[u]) if (v != p)
    dep[v] = dep[u] + 1, dfs(v, u);
  int out = t-1; max_d = max(max_d, dep[u]);
  queries.emplace_back(in, out, u);
}

vector<pair<int, int>> nxt[N];

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

int calc1(int i, int d, int t) {
  if (t == 1) return d; 
  ll ans = pw(t, i + d) - pw(t, i);
  if (ans < 0) ans += M;
  ans = 1LL * ans * pw(t + M - 1, M - 2) % M;
  return ans;
}

int calc(ll x, ll y, ll t, ll d, ll m) {
  // [x*t^0 + .. + x*t^d] + [(x+1)*t^(d+1) + .. + (x+1)*t^2d] + .. + [(x+k-1)]
  ll k = y - x + 1;
  if (t == 1) {
    ll ans = y * (y + 1) % M * pw(2, M - 2) % M;
    ans -= x * (x + M - 1) % M * pw(2, M - 2) % M; if (ans < 0) ans += M;
    ans = ans * d % M;
    return ans;
  }
  
  ll ans = -(k + x) % M; if (ans < 0) ans += M;
  ans = ans * pw(t, d * k) % M; 
  ans += (k + x - 1) * pw(t, d * (k + 1)) % M; if (ans >= M) ans -= M;
  ans -= (x + M - 1) * pw(t, d) % M; if (ans < 0) ans += M;
  ans += x; if (ans >= M) ans -= M;
  ans = ans * pw(t - 1, M - 2) % M; 
  ans = ans * pw(pw(t, d) - 1, M - 2) % M;
  ans = ans * pw(t, m) % M;
  return ans;  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; 
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs();
  sort(queries.begin(), queries.end());
  int l = 0, r = -1; 
  for (auto& q : queries) {
    while (l > q.l) cnt[dep[a[--l]]]++;
    while (l < q.l) cnt[dep[a[l++]]]--;
    while (r < q.r) cnt[dep[a[++r]]]++;
    while (r > q.r) cnt[dep[a[r--]]]--;
    
    for (int cur = dep[q.i]; cur <= max_d; cur++) {
      for (int i = 16; ~i; --i) 
        if (cur + (1 << i) <= max_d && cnt[cur + (1 << i)] == cnt[cur])
          cur += 1 << i;
      nxt[q.i].emplace_back(cur, cnt[cur]); 
    }
  }
  for (int i = 0, u, t, p_u = 0, p_t = 0; i < m; ++i) {
    cin >> u >> t; 
    int res = 0;
    u += p_u; u %= n;
    t += p_t; t %= M9; t++;
    int x = 0, m = 0;
    for (auto& p : nxt[u]) {
      int y, d; tie(y, d) = p; y -= dep[u];
      res += calc(x, y, t, d, m);
      if (res >= M) res -= M; 
      m += (y - x + 1) * d, x = y + 1;
    }
    cout << res << '\n';
    p_u += res % n; if (p_u >= n) p_u -= n;
    p_t += res % M9; if (p_t >= M9) p_t -= M9;
  }
	return 0;
}

