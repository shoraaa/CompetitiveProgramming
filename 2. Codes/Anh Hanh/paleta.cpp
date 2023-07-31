#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e6 + 5, M = 998244353;

int dp[N], pw[N]; 
vector<int> adj[N];
int f[N], dep[N];
bitset<N> vis;
int n, k, cnt, len;

inline int add(int x, int y) {
  if ((x += y) >= M) x -= y; return x;
}

inline int sub(int x, int y) {
  if ((x -= y) < 0) x += M; return x;
}

void dfs(int u) {
  vis[u] = 1; cnt++;
  for (int v : adj[u])
    if (!vis[v]) 
      dep[v] = dep[u] + 1, dfs(v);
    else if (dep[v] < dep[u] - 1)
      len = dep[u] - dep[v] + 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  if (fopen("paleta.inp", "r")) 
    freopen("paleta.inp", "r", stdin),
    freopen("paleta.out", "w", stdout);
  int subtask; cin >> subtask;
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> f[i], adj[i].reserve(2);
  for (int i = 1; i <= n; i++) {
    if (f[i] == i) continue;
    adj[i].emplace_back(f[i]);
    if (f[f[i]] != i)
      adj[f[i]].emplace_back(i);
  }
  pw[0] = 1; dp[0] = 0;
  pw[1] = k - 1; dp[1] = k;
  pw[2] = 1LL * (k - 1) * (k - 1) % M;
  dp[2] = 1LL * k * (k - 1) % M;
  for (int i = 3; i <= n; i++) {
    dp[i] = sub(1LL * k * pw[i - 1] % M, dp[i - 1]);
    pw[i] = 1LL * pw[i - 1] * (k - 1) % M;
  }
  ll res = 1;
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    cnt = 0; len = -1; dfs(i);
    if (len > 0) {
      res = res * dp[len] % M * pw[cnt - len] % M;
    } else {
      res = res * k % M * pw[cnt - 1] % M;
    }
  }
  cout << res << '\n';
}