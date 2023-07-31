#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<pair<int, int>> adj[N];
int a[N]; ll cur[N];
int n, m; ll k;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("staff.inp", "r"))
    freopen("staff.inp", "r", stdin),
    freopen("staff.out", "w", stdout);
    
  int T; cin >> n >> m >> T;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  vector<tuple<int, int, int>> edges;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(u, v, w),
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  while (T--) {
    cin >> k;
    for (int i = 0; i < n; ++i)
      cur[i] = a[i];
    for (auto& p : edges) {
      int u, v, w; tie(u, v, w) = p;
      cur[u] += w, cur[v] += w;
    }
    set<pair<ll, int>> st;
    for (int i = 0; i < n; ++i) 
      st.insert({cur[i], i});
    while (!st.empty() && st.begin()->fi <= k) {
      int u = st.begin()->se; st.erase(st.begin());
      for (auto& p : adj[u]) {
        int v, w; tie(v, w) = p; 
        auto it = st.find({cur[v], v});
        if (it == st.end()) continue;
        st.erase(it); cur[v] -= w; st.insert({cur[v], v});
      }
    }
    cout << st.size() << ' ';
  }
	return 0;
}

