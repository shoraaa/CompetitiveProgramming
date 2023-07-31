#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int R = 61, C = 10, M = 1e9 + 19972207;

inline void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

int dp1[R][1 << C][1 << C], dp2[R][1 << C][1 << C];
int mask1[1 << C], mask2[1 << C], f[1 << C], ans[R][1 << C], res[R][C];

int n, m;
int a[R];

#define bit_count(x) (__builtin_popcount(x))

void calc(int dp[][1<<C][1<<C]) {
  for (int msk = 0; msk < 1 << m; ++msk) {
    if (a[1] != 3 && bit_count(msk) % 3 != a[1]) continue;
    dp[1][msk][0] = 1;
  }
  
  for (int i = 2; i <= n; ++i) {
    // co dinh hang truoc do
    for (int msk1 = 0; msk1 < 1 << m; ++msk1) {
      if (a[i - 1] != 3 && bit_count(msk1) % 3 != a[i - 1]) continue;

      // f[msk] = tong cua moi dp[i - 1][msk1][sub_mask]
      for (int msk = 0; msk < 1 << m; ++msk) {
        f[msk] = dp[i - 1][msk1][msk];
      }
      
      // dp sos
      for (int i = 0; i < m; ++i) {
        for (int msk = 0; msk < 1 << m; ++msk) {
          if (msk >> i & 1) {
            add(f[msk], f[msk ^ (1 << i)]);
          }
        }
      }
      
      // tinh dp[i][msk][msk1]
      for (int msk = 0; msk < 1 << m; ++msk) {
        if (a[i] != 3 && bit_count(msk) % 3 != a[i]) continue;
        if (msk1 & mask1[msk]) continue;
        int msk2 = (mask2[msk] | mask1[msk1]) ^ ((1 << m) - 1);
        add(dp[i][msk][msk1], f[msk2]);
      }
      
    }
    
  }
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("tetquymao.inp", "r"))
    freopen("tetquymao.inp", "r", stdin),
    freopen("tetquymao.out", "w", stdout);
  cin >> n >> m;
  
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  
  for (int msk = 0; msk < 1 << m; ++msk) {
    // nhung o bi chan o hang i-1 khi hang i la msk
    int res = 0;
    for (int i = 0; i < m; ++i) {
      if (msk >> i & 1) {
        if (i - 2 >= 0) res |= 1 << (i - 2);
        if (i + 2 < m) res |= 1 << (i + 2);
      }
    }
    mask1[msk] = res;
  }
  
  for (int msk = 0; msk < 1 << m; ++msk) {
    // nhung o bi chan o hang i-2 khi hang i la msk
    int res = 0;
    for (int i = 0; i < m; ++i) {
      if (msk >> i & 1) {
        if (i - 1 >= 0) res |= 1 << (i - 1);
        if (i + 1 < m) res |= 1 << (i + 1);
      }
    }
    mask2[msk] = res;
  }
  
  calc(dp1);
  reverse(a + 1, a + n + 1);
  calc(dp2);
  reverse(a + 1, a + n + 1);
  // hang i la hang n - i + 1 trong dp2
  
  for (int i = 1; i <= n; ++i) {
    // co dinh hang i
    for (int msk1 = 0; msk1 < 1 << m; ++msk1) {  
      if (a[i] != 3 && bit_count(msk1) % 3 != a[i]) continue;

      // f[msk] = tong cua moi dp2[i][msk1][sub_mask]
      for (int msk = 0; msk < 1 << m; ++msk) {
        f[msk] = dp2[n - i + 1][msk1][msk];
      }
      
      // dp sos
      for (int i = 0; i < m; ++i) {
        for (int msk = 0; msk < 1 << m; ++msk) {
          if (msk >> i & 1) {
            add(f[msk], f[msk ^ (1 << i)]);
          }
        }
      }
      
      for (int msk = 0; msk < 1 << m; ++msk) {
        if (msk & mask1[msk1]) continue;
        int msk2 = (mask1[msk1] | mask2[msk]) ^ ((1 << m) - 1);
        add(ans[i][msk1], 1LL * dp1[i][msk1][msk] * f[msk2] % M);
      }
      
    }
  }
  
  for (int i = 1; i <= n; ++i) {
    for (int msk = 0; msk < 1 << m; ++msk) {
      for (int j = 0; j < m; ++j) {
        if (msk >> j & 1) {
          add(res[i][j], ans[i][msk]);
        }
      }
    }
  }
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << res[i][j] << ' ';
    }
    cout << '\n';
  }
  
  
  
	return 0;
}

