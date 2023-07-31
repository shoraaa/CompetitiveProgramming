#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 341055;
ll state[N];

int n, m, id = 0;
ll cur_set = 0;
void gen(int i, int s) {
  if (s == 4) {
    state[id] = cur_set; id++;
    return;
  }
  if (i == -1) return;
  gen(i - 1, s);
  cur_set ^= 1LL << i;
  gen(i - 1, s + 1);
  cur_set ^= 1LL << i;
}

int r[10], c[10], row[60], col[60], cnt_r[10], cnt_c[10], a[60], dp[60][N], C[60][5];
#define first_bit(x) (63 - __builtin_clzll(x))

int get(ll msk) {
  int id = 0;
  for (ll msk2 = msk, k, i = 4; msk2; --i) {
    k = first_bit(msk2); msk2 ^= 1LL << k;
    id += C[k][i];
  }
  return id;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= 5; ++i) cin >> r[i];
  for (int i = 1; i <= 5; ++i) cin >> c[i];
  
  m += 5; gen(m - 1, 0);
  
  for (int i = 0; i < m; ++i)
    cin >> a[i], a[i]--, row[i] = a[i] / n, col[i] = a[i] % n;
  
  C[0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= 4; ++j) {
      C[i + 1][j] += C[i][j];
      if (j <= 3) C[i + 1][j + 1] += C[i][j];
    }
  }
  
  memset(dp, -0x3f, sizeof(dp));
  int INF = dp[0][0];
  dp[4][0] = 0;
  
  int res = 0;
  for (int i = 4; i < m; ++i) {
    for (int j = 0; j < id; ++j) {
      if (dp[i][j] == INF) continue;
      
      res = max(res, dp[i][j]);

      if (i == m - 1) continue;
      cnt_r[row[i + 1]]++, cnt_c[col[i + 1]]++;
      
      for (ll msk1 = state[j], k; msk1;) {
        k = first_bit(msk1); msk1 ^= 1LL << k;
        cnt_r[row[k]]++, cnt_c[col[k]]++;
      }
      
      int c_r = 0, c_c = 0;
      for (int i = 0; i < n; ++i) 
        c_r = max(c_r, cnt_r[i]), 
        c_c = max(c_c, cnt_c[i]);
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + r[c_r] + c[c_c]);
      
      cnt_r[row[i]]++, cnt_c[col[i]]++;
      for (ll msk1 = state[j], k; msk1;) {
        k = first_bit(msk1); msk1 ^= 1LL << k;
        cnt_r[row[k]]--, cnt_c[col[k]]--;
        
        ll nxt = get((state[j] ^ (1LL << k)) | (1LL << i));
        int c_r = 0, c_c = 0;
        for (int i = 0; i < n; ++i) 
          c_r = max(c_r, cnt_r[i]), 
          c_c = max(c_c, cnt_c[i]);
        dp[i + 1][nxt] = max(dp[i + 1][nxt], dp[i][j] + r[c_r] + c[c_c]);
        
        cnt_r[row[k]]++, cnt_c[col[k]]++;
      }
      cnt_r[row[i]]--, cnt_c[col[i]]--;
      
      for (ll msk1 = state[j], k; msk1;) {
        k = first_bit(msk1); msk1 ^= 1LL << k;
        cnt_r[row[k]]--, cnt_c[col[k]]--;
      }
      cnt_r[row[i + 1]]--, cnt_c[col[i + 1]]--;
      
    }
  }
  
  cout << res;
  
	return 0;
}
