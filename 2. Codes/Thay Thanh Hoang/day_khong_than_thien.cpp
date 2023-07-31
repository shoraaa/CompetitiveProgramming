#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
int a[N];
vector<pair<int, int>> dp[N];
#define fi first
#define se second
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T; dp[0].emplace_back(0, -1);
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> a[i], dp[i].clear();
    int res = 0;
    vector<int> idx = {0};
    for (int i = 1; i <= n; ++i) {
      int id = -1; map<int, int> mp;
      for (int j : idx) if (a[j] != a[i]) {
        for (auto& d : dp[j]) if (d.se != a[i]) 
          mp[a[j]] = max(mp[a[j]], d.fi + 1),
          res = max(res, d.fi + 1);
      } else id = j;
      for (auto it = mp.rbegin(); it != mp.rend(); it++) {
        dp[i].emplace_back(it->se, it->fi);
        if (dp[i].size() == 6) break;
      }
      if (id != -1) idx.erase(find(idx.begin(), idx.end(), id));
      else if (idx.size() == 6) idx.erase(idx.begin());
      idx.emplace_back(i);
    }
    cout << res << '\n';
  }
	return 0;
}

