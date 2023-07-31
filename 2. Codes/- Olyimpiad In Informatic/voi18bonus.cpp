#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const int INF = 1e9;

ll f[505][505];
int n, k, r, p;
ll get(int l, int r, int t, int d) {
  if (l > r || t > d) return 0;
  return f[d][r] - f[d][l - 1] - f[t - 1][r] + f[t - 1][l - 1];
}

struct Rectangle {
  int l, r, d, t;
} a[5];

#define bit_count(x) (__builtin_popcount(x))

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> r >> p;
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> f[i][j];
      f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
    }
  }

  ll res = 0;
  
  for (int i = 1; i <= k; ++i) {
    
    for (int i = 0, x, y; i < p; ++i) {
      cin >> a[i].t >> a[i].l;
      a[i].r = a[i].l + r - 1;
      a[i].d = a[i].t + r - 1;
    }
    
    ll cur = 0;
    for (int msk = 1; msk < 1 << p; ++msk) {
      
      int l = -INF, t = -INF, r = INF, d = INF;
      
      for (int i = 0; i < p; ++i) {
        if (msk >> i & 1) {
          
          l = max(l, a[i].l);
          r = min(r, a[i].r);
          t = max(t, a[i].t);
          d = min(d, a[i].d);
          
        }
        
      }
      
      ll sum = get(l, r, t, d), cnt = bit_count(msk);
      if (cnt % 2 == 1) {
        cur += sum;
      } else {
        cur -= sum;
      }
      
    }
    
    res = max(res, cur);
    
  }
  
  cout << res;
  
  
  
  
	return 0;
}
