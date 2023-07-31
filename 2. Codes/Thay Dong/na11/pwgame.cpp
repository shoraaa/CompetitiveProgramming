#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 10;
string s[N];
int n, m;

#define popcount(x) __builtin_popcount(x)
#define first(x) (__builtin_ffs(x) - 1)

int dp[N / 2][1 << N][1 << N][2];
int call(int c, int msk1, int msk2, int p) {
  
  if (m % 2 == 1 && c == m / 2) return 0;
  
  if (~dp[c][msk1][msk2][p]) return dp[c][msk1][msk2][p];
  // nguoi se thang neu xet cot c, tt msk1,2 nguoi dang di la p
  if (popcount(msk1) == 1 && popcount(msk2) == 1) 
    return s[first(msk1)][c] == s[first(msk2)][m - c - 1] ? 0 : 1;
  
  if (popcount(msk1) > 1) {
    for (int cur = msk1; cur > 0;) {
      int i = first(cur); cur ^= 1 << i;
      if (call(c, msk1 ^ (1 << i), msk2, !p) == p) 
        return dp[c][msk1][msk2][p] = p;
    }
  }
  
  if (popcount(msk2) > 1) {
    for (int cur = msk2; cur > 0;) {
      int i = first(cur); cur ^= 1 << i;
      if (call(c, msk1, msk2 ^ (1 << i), !p) == p) 
        return dp[c][msk1][msk2][p] = p;
    }
  }
  
  return dp[c][msk1][msk2][p] = !p;
}

int check1() {
  // 1 thang di dau thang va tat ca cac thang con lai di 2 kieu van thang
  for (int i = 0; i < (m + 1) / 2; ++i) if (call(i, (1 << n) - 1, (1 << n) - 1, 0) == 0) {
    int flag = 1;
    for (int j = 0; j < (m + 1) / 2; ++j) if (j != i)
      flag &= (call(j, (1 << n) - 1, (1 << n) - 1, 0) == 0) 
           && (call(j, (1 << n) - 1, (1 << n) - 1, 1) == 0);
    if (flag) return 1;
  }
  return 0;
}

int check2() {
  // di sau thang 
  int flag = 1;
  for (int i = 0; i < (m + 1) / 2; ++i)
    flag &= call(i, (1 << n) - 1, (1 << n) - 1, 1) == 0;
  if (flag) return 1;
  // di truoc thang va cac o con lai di sau thang
  for (int i = 0; i < (m + 1) / 2; ++i) if (call(i, (1 << n) - 1, (1 << n) - 1, 0) == 0) {
    flag = 1;
    for (int j = 0; j < (m + 1) / 2; ++j) if (j != i)
      flag &= (call(j, (1 << n) - 1, (1 << n) - 1, 1) == 0);
    if (flag) return 1;
  }
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
      cin >> s[i];
    
    memset(dp, -1, sizeof(dp));
    if (m % 2 == 0 || n % 2 == 1) 
      cout << (check1() ? "Elly\n" : "Kriss\n");
    else {
      cout << (check2() ? "Elly\n" : "Kriss\n");
    }
  }
	return 0;
}
