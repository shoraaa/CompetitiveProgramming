#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, BLOCK = 400;
vector<int> S[N];
vector<pair<int, int>> G[N];
int vis[N];
ll a[N], b[N], c[N];
int n, m, q;
int intersection(vector<int>& v) {
  int res = 0;
  for (int x : v) res += vis[x];
  return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);  
	cin >> n >> m >> q;
	for (int i = 0; i < n; ++i)
	  cin >> a[i];
	for (int i = 0, k, idx; i < m; ++i) {
	  cin >> k; S[i].reserve(k);
	  while (k--) cin >> idx, idx--, S[i].emplace_back(idx);
	}
	for (int i = 0; i < m; ++i) if (S[i].size() > BLOCK) {
	  memset(vis, 0, sizeof(vis));
	  for (int j : S[i]) vis[j] = 1, c[i] += a[j];
	  for (int j = 0, is; j < m; ++j) if (j != i && (is = intersection(S[j])))
	    G[j].emplace_back(i, is);
	}
	char ch; ll x; int k;
	while (q--) {
	  cin >> ch >> k; k--;
	  if (ch == '?') {
	    ll res = 0;
	    if (S[k].size() <= BLOCK) for (int i : S[k]) res += a[i];
	    else res = c[k];
	    for (auto& p : G[k]) res += b[p.first] * p.second;
	    cout << res << '\n';
	  } else {
	    cin >> x;
	    if (S[k].size() <= BLOCK) {
	      for (int i : S[k]) a[i] += x;
	      for (auto& p : G[k]) c[p.first] += x * p.second;
	    } else b[k] += x;
	    c[k] += x * S[k].size();
	  }
	}
	return 0;
}

