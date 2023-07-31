#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;

int n;
vector<int> divi[N], dp[N];

vector<pair<int, int>> adj[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  
  vector<int> d;
  for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
    d.emplace_back(i);
    if (i * i != n) d.emplace_back(n / i);
  }
  d.emplace_back(n);
  sort(d.begin(), d.end());
  
  for (int i = 0; i < d.size(); ++i) {
    for (int j = 0; j < i; ++j) if (d[i] % d[j] == 0) {
      int k = lower_bound(d.begin(), d.end(), d[i] / d[j]) - d.begin();
      adj[i].emplace_back(j, k);
    }
  }

  dp[d.size() - 1].emplace_back(0);
  
  set<int> ans;
  
  for (int i = d.size() - 1; ~i; --i) {
    sort(dp[i].begin(), dp[i].end());
    dp[i].erase(unique(dp[i].begin(), dp[i].end()), dp[i].end());
    
    for (int s : dp[i]) {
      ans.insert(s + d[i] - 1);
    }
    
    for (auto& p : adj[i]) {
      int j, k; tie(j, k) = p;
      for (int s : dp[i]) {
        dp[k].emplace_back(s + d[j] - 1);
      }
    }
  }
  
  cout << ans.size() << '\n';
  for (int x : ans) {
    cout << x << ' ';
  }
  
  
  
	return 0;
}

