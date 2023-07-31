#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
int a[N], cnt[2][N];
vector<pair<int, int>> val[2];
int n;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n; val[0].clear(); val[1].clear();
    for (int i = 0; i < n; ++i)
      cin >> a[i], cnt[i&1][a[i]]++;
    for (int t = 0; t < 2; ++t) val[t].clear();
    for (int i = 1; i <= n; ++i) 
      for (int t = 0; t < 2; ++t) if (cnt[t][i])
        val[t].emplace_back(cnt[t][i], i), cnt[t][i] = 0;
    for (int t = 0; t < 2; ++t) sort(val[t].rbegin(), val[t].rend());
    int res = 1e9;
    for (int u = 0; u < min((int)val[0].size(), 8); ++u) {
      for (int v = 0; v < min((int)val[1].size(), 8); ++v) {
        vector<int> V = { val[0][u].se, val[1][v].se };
        if (V[0] == V[1]) continue;
        // ans = (n+1)/2 - C.fi + (n/2) - L.fi + Z (len / 2);
        int cur = (n + 1) / 2 - val[0][u].fi + (n / 2) - val[1][v].fi;
        for (int i = 0; i < n; ++i) if (a[i] == V[(i&1)^1]) {
          int j = i;
          while (j < n && a[j] == V[(j&1)^1]) j++;
          cur += (j - i) / 2; i = j - 1;
        }
        res = min(res, cur);
      }
    }
    cout << res << '\n';
    
  }
	return 0;
}

