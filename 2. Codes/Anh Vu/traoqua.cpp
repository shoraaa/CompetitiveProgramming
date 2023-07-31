#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int par[N], cnt[N];
bitset<N> dp, vis;
int n, k, m = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k; 
  for (int u = 0; u < n; ++u)
    cin >> par[u], par[u]--;
  int chan = 0, le = 0;
  for (int u = 0; u < n; ++u) if (!vis[u]) {
    int v = u, len = 0;
    while (!vis[v]) {
      vis[v] = 1, v = par[v], len++;
    }
    chan += len / 2;
    if (len & 1) le++;
    m = max(len, m);
    cnt[len]++;
  }
  for (int i = 2; i <= m; ++i) if (cnt[i] > 1) {
    if (cnt[i] & 1) cnt[i * 2] += cnt[i] / 2, cnt[i] = 1;
    else cnt[i * 2] += cnt[i] / 2 - 1, cnt[i] = 2;
    m = max(m, i * 2);
  }
  dp[0] = 1;
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= cnt[i]; ++j) 
      dp |= dp << i;
  cout << (dp[k] ? k : k + 1) << ' ' << min(k, chan) * 2 + min(max(0, k-chan), le);
	return 0;
}

