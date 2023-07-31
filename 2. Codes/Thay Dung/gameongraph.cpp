#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int n, m;

int lin[N];
int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}

int erased[N];
stack<int> st;
set<int> in[N], out[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) lin[i] = i; 
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--, 
    in[v].insert(u), out[u].insert(v);
  
  
  for (int i = 0; i < n; ++i) 
    if (out[i].size() == 0) st.push(i);
  while (!st.empty()) {
    int u = st.top(); st.pop(); erased[u] = 1; 
    for (int v : in[u]) {
      v = find(v); out[v].erase(u);
      if (out[v].size() == 0) st.push(v);
    }
  }
  
  for (int i = 0; i < n; ++i) 
    if (out[i].size() == 1) st.push(i);
  while (!st.empty()) {
    int u = find(st.top());
    int v = find(*out[st.top()].begin());
    st.pop(); 
    if (u == v) continue;
    if (in[u].size() > in[v].size()) swap(u, v);
    for (int x : in[u]) {
      out[x].erase(u); out[x].insert(v);
      if (out[x].size() == 1) st.push(x);
      in[v].insert(x);
    }
    lin[u] = v; in[u].clear(); 
  }

  int q; cin >> q;
  while (q--) {
    int u, v; cin >> u >> v; u--, v--; u = find(u), v = find(v);
    if (erased[u] || erased[v] || u == v) cout << 'B';
    else cout << 'H';
  }
	return 0;
}
