#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
vector<int> adj[N][2];
int a[N], d[N][2];
bool vis[N][2];
queue<pair<int, bool>> q[3];  
int n, m;
#define getchar_unlocked getchar
inline void scan_uint(int& p) {
  static char c;
  while ((c = getchar_unlocked()) < '0'); // just to be safe
  for (p = c-'0'; (c = getchar_unlocked()) >= '0'; p = p*10+c-'0');
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("graph01.INP", "r"))
    freopen("graph01.INP", "r", stdin),
    freopen("graph01.OUT", "w", stdout);
  scan_uint(n), scan_uint(m);
  for (int i = 0; i < n; ++i)
    scan_uint(a[i]);
  for (int i = 0, u, v, w; i < m; ++i)
    scan_uint(u), scan_uint(v), scan_uint(w), u--, v--,
    adj[u][w].emplace_back(v),
    adj[v][w].emplace_back(u);
  memset(d, 0x3f, sizeof(d)); int inf = d[0][0];
  q[a[0]].emplace(0, 0);
  q[a[0]].emplace(0, 1);
  d[0][0] = d[0][1] = a[0];
  int pos = 0, num = 2;
  while (num > 0) {
    while (q[pos % 3].empty()) ++pos;
    auto s = q[pos % 3].front();
    q[pos % 3].pop(); num--;
    int u = s.first, t = s.second;
    if (vis[u][t]) continue;
    vis[u][t] = 1; int w = t^a[u];
    for (int v : adj[u][w]) { 
      if (d[u][t] + w + a[v] < d[v][w]) 
        d[v][w] = d[u][t] + w + a[v], 
        q[d[v][w] % 3].emplace(v, w),
        num++; 
      }
  }
  int res = min(d[n-1][0], d[n-1][1]);
  if (res == inf) cout << -1;
  else cout << res;
	return 0;
}
