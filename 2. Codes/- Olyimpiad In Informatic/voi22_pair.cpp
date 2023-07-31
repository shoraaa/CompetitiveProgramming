#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
int a[N];
int n, d;

// struct Pair {
  // int sum, i, j;
  // Pair(int sum, int i, int j): sum(sum), i(i), j(j) {}
  // bool operator < (const Pair& p) const {
    // return sum < p.sum;
  // }
// };
// 
int vis[N];
vector<pair<int, int>> b[N * N];
vector<pair<int, int>> c;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("pair.inp", "r")) {
    freopen("pair.inp", "r", stdin);
    freopen("pair.out", "w", stdout);
  }
  
  cin >> n >> d;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  
  vector<int> sum;
  sum.reserve(n * n);
  
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      sum.emplace_back(a[i] + a[j]);
    }
  }
  
  sort(sum.begin(), sum.end());
  sum.erase(unique(sum.begin(), sum.end()), sum.end());
  
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int k = lower_bound(sum.begin(), sum.end(), a[i] + a[j]) - sum.begin();
      b[k].emplace_back(i, j);
    }
  }
  
  int res = 0;
  for (int i = 0; i < sum.size(); ++i) {
    if (d == 1) {
      int k = lower_bound(sum.begin(), sum.end(), sum[i] + 1) - sum.begin();
      if (sum[k] == sum[i] + 1) {
        for (auto& p : b[k]) {
          b[i].emplace_back(p);
        }
      }
    }
      
    sort(b[i].begin(), b[i].end(), [](pair<int, int>& u, pair<int, int>& v) {
      if (u.fi == v.fi) return u.se > v.se;
      return u.fi < v.fi;
    });
    
    for (auto& p : b[i]) {
      vis[p.fi] = vis[p.se] = 0;
    }
    
    int cur = 0;
    for (auto& p : b[i]) {
      if (!vis[p.fi] && !vis[p.se]) {
        vis[p.fi] = vis[p.se] = 1;
        cur++;
      }
    }
    res = max(res, cur);
    
    vector<pair<int, int>>().swap(b[i]);
    
  }
  
  cout << res;
  
	return 0;
}
