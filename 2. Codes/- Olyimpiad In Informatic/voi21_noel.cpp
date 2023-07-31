#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
const int INF = 1e9;

int a[N], idx[N];

int n, d;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> d;
  
  int res = 0;
  
  for (int i = 1; i <= n * 2; ++i) {
    cin >> a[i];
    idx[a[i]] = i;
  }
  
  for (int k = 1; k < n * 2; ++k) {
    // [1, k] va [k+1, n]
    vector<int> lis;
    
    for (int i = 1; i <= k; ++i) {
      vector<int> vec;
      for (int x = max(1, a[i] - d); x <= min(n * 2, a[i] + d); ++x) {
        if (idx[x] > k) {
          vec.emplace_back(idx[x]);
        }
      }
      sort(vec.rbegin(), vec.rend());
      
      for (int i : vec) {
        lis.emplace_back(i);
      }
      
    }
    
    // for (int i : lis) {
      // cerr << i << ' ';
    // }
    // cerr << endl;
    
    vector<int> f(n * 2 + 1, INF);
    f[0] = -INF;
    
    int ans = 0;
    
    for (int x : lis) {
      // vi tri lon nhat ma f[k] < x + 1 = vi tri nho nhat ma f[k] >= x
      int len = lower_bound(f.begin(), f.end(), x) - f.begin();
      f[len] = x;
      ans = max(ans, len);

    }
    
    res = max(res, ans);
    
  }
  
  cout << res;
  
	return 0;
}

