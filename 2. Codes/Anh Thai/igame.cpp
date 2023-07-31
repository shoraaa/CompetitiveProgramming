#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e6 + 5;
vector<int> adj[N];
int f[N]; // so cach thang khi doi thu vua an dinh u
int n;

int ans[N];
void dfs(int u = 0, int p = -1) {
  for (int v : adj[u]) if (v != p)
    dfs(v, u), f[u] += f[v] == 0;
}
void dfs2(int u = 0, int p = -1) {
  ans[u] = f[u] == 0;
  for (int v : adj[u]) if (v != p) {
    f[u] -= f[v] == 0;
    f[v] += f[u] == 0;
    dfs2(v, u);
    f[v] -= f[u] == 0;
    f[u] += f[v] == 0;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int u = 1, v; u < n; ++u)
    cin >> v, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  if (n == 1)
    return cout << 1, 0;
  dfs();
  dfs2();
  for (int i = 0; i < n; ++i) if (ans[i])
    cout << i + 1 << '\n';
	return 0;
}

