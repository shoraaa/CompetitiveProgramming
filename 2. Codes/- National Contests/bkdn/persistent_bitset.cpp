#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3, Q = 1e5 + 5;
using row = bitset<N>;
int n, m, q;
vector<vector<int>> tl;
struct Query {
  int type, i, j;
  Query(int type, int i, int j): type(type), i(i), j(j) {}
};
vector<Query> que;
int vis[Q], idx[Q];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  for (int t = 1, i, j, k, type, res; t <= q; ++t) {
    cin >> type >> i;
    if (type <= 2) cin >> j;
    que.emplace_back(type, i, j);
    if (type == 4) vis[i] = 1;
  }
  row flip; vector<row> state; state.emplace_back(flip); 
  for (int i = 0; i < m; ++i) flip[i] = 1;
  
  vector<int> cur(n); tl.reserve(q); 
  
  idx[0] = tl.size(),
  tl.emplace_back(cur);
  for (int t = 1, i, j, k, type, res; t <= q; ++t) {
    auto qu = que[t - 1];
    type = qu.type, i = qu.i, j = qu.j;
    if (type == 1) {
      i--, j--;
      row nxt = state[cur[i]]; nxt[j] = 1;
      cur[i] = state.size();
      state.emplace_back(nxt);
    } else if (type == 2) {
      i--, j--;
      row nxt = state[cur[i]]; nxt[j] = 0;
      cur[i] = state.size();
      state.emplace_back(nxt);
    } else if (type == 3) {
      i--;
      row nxt = state[cur[i]]; nxt ^= flip;
      cur[i] = state.size();
      state.emplace_back(nxt);
    } else { 
      cur = tl[idx[i]];
    }
    res = 0;
    for (int i = 0; i < n; ++i) 
      res += state[cur[i]].count();
    cout << res << '\n';
    if (vis[t]) 
      idx[t] = tl.size(),
      tl.emplace_back(cur);    
  } 
	return 0;
}

