#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4e5 + 5;
int a[N], c[N];
int n, d, m = 0;

struct BIT {
  int bit[N];
  int get(int i) {
    i = upper_bound(c, c + m, i) - c;
    int res = 0;
    for (; i; i -= i & -i) {
      res = max(res, bit[i]);
    }
    return res;
  }
  void update(int i, int v) {
    i = lower_bound(c, c + m, i) - c + 1;
    for (; i <= m; i += i & -i) {
      bit[i] = max(bit[i], v);
    }
  }
} bit1, bit2;

int f[N][2];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> d;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    c[m++] = a[i];
  }
  sort(c, c + m);
  m = unique(c, c + m) - c;
  
  int res = 0;
  
  for (int i = 1; i <= n; ++i) {
    
    f[i][0] = bit1.get(a[i] - 1) + 1;
    f[i][1] = max(bit2.get(a[i] - 1) + 1, bit1.get(a[i] + d - 1) + 1);
    
    bit1.update(a[i], f[i][0]);
    bit2.update(a[i], f[i][1]);
    
    res = max(res, f[i][0]);
    res = max(res, f[i][1]);
    
  }
  
  cout << res;
  
	return 0;
}

