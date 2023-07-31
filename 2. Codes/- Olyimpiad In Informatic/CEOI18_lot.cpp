#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 5;
int a[N];
int n, l, q;

int ans[105][N];
int kq[105];
int queries[105];

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> l;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> kq[i];
    queries[i] = kq[i];
  }
  
  sort(kq + 1, kq + q + 1);
  int m = unique(kq + 1, kq + q + 1) - kq - 1;
  kq[m + 1] = n + 1;
  
  for (int k = 1; l + k <= n; ++k) {
    
    int dif = 0;
    for (int i = 1; i <= l; ++i) {
      dif += a[i] != a[i + k];
    }
    
    int j = 1;
    while (kq[j] < dif) j++;
    
    ans[j][1]++;
    ans[j][1 + k]++;
    
    
    for (int i = 2; i + k + l - 1 <= n; ++i) {
      dif -= a[i - 1] != a[i + k - 1];
      dif += a[i + l - 1] != a[i + k + l - 1];
      while (kq[j] < dif) j++;
      while (j - 1 >= 1 && kq[j - 1] >= dif) j--;
      ans[j][i]++;
      ans[j][i + k]++;
    }
  }
  
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n - l + 1; ++j) {
      ans[i][j] += ans[i - 1][j];
    }
  }
  
  for (int i = 1; i <= q; ++i) {
    int id = lower_bound(kq + 1, kq + m + 1, queries[i]) - kq;
    for (int j = 1; j <= n - l + 1; ++j) {
      cout << ans[id][j] << ' ';
    }
    cout << '\n';
  }
  
	return 0;
}

