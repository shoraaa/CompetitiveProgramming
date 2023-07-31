#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "domino";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5;
int a[N], b[N], lef[N], rig[N], col[N];
vector<int> pos[N];
int n;
int dfs(int u, int c) {
  if (u == 0) return 1;
  if (!~col[u]) col[u] = c;
  else return col[u] == c;
  return dfs(lef[u], c^1) && dfs(rig[u], c^1);
}
int solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    pos[i].clear(), lef[i] = rig[i] = 0, col[i] = -1;
  for (int i = 1; i <= n; ++i)
    cin >> a[i] >> b[i], 
    pos[a[i]].emplace_back(i),
    pos[b[i]].emplace_back(i);
  for (int i = 1; i <= n; ++i) {
    if (a[i] == b[i]) return 0;
    if (pos[a[i]].size() > 2 || pos[b[i]].size() > 2) return 0;
    if (pos[a[i]].size() == 2)
      lef[i] = pos[a[i]][0] ^ pos[a[i]][1] ^ i;
    if (pos[b[i]].size() == 2)
      rig[i] = pos[b[i]][0] ^ pos[b[i]][1] ^ i;
  }
  for (int i = 1; i <= n; ++i) if (!~col[i]) { 
    if (!dfs(i, 0)) return 0;
  }
  return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  int T;
  cin >> T;
  while (T--) 
    cout << (solve() ? "Yes\n" : "No\n");
	return 0;
}

