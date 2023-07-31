#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

const int N = 30;
int dp[N][N][N][N][12][4];
int p[15], nxt[15][26];
string s[N], t;
int n, m, k;

int TT(int r1, int c1, int r2, int c2, int v);
int TP(int r1, int c1, int r2, int c2, int v);
int DT(int r1, int c1, int r2, int c2, int v);
int DP(int r1, int c1, int r2, int c2, int v);

int TT(int r1, int c1, int r2, int c2, int v) {
  if (~dp[r1][c1][r2][c2][v][0]) return dp[r1][c1][r2][c2][v][0];
  
  if (r1 == r2) {
    int nv = v;
    for (int c = c1; c <= c2; ++c) 
      nv = nxt[nv][s[r1][c] - 'A'];
    return dp[r1][c1][r2][c2][v][0] = nv == k;
  }
  
  int res = 0;
  for (int c = c1, nv = v; c <= c2; ++c) {
    nv = nxt[nv][s[r1][c] - 'A'];
    res += TP(r1 + 1, c1, r2, c, nv);
  }
  return dp[r1][c1][r2][c2][v][0] = res;
}

int TP(int r1, int c1, int r2, int c2, int v) {
  if (~dp[r1][c1][r2][c2][v][1]) return dp[r1][c1][r2][c2][v][1];
  
  if (c1 == c2) {
    int nv = v;
    for (int r = r1; r <= r2; ++r) 
      nv = nxt[nv][s[r][c2] - 'A'];
    return dp[r1][c1][r2][c2][v][1] = nv == k;
  }
  
  int res = 0;
  for (int r = r1, nv = v; r <= r2; ++r) {
    nv = nxt[nv][s[r][c2] - 'A'];
    res += DP(r1, c1, r, c2 - 1, nv);
  }
  return dp[r1][c1][r2][c2][v][1] = res;
}

int DP(int r1, int c1, int r2, int c2, int v) {
  if (~dp[r1][c1][r2][c2][v][2]) return dp[r1][c1][r2][c2][v][2];
  
  if (r1 == r2) {
    int nv = v; 
    for (int c = c2; c >= c1; --c) 
      nv = nxt[nv][s[r2][c] - 'A'];
    return dp[r1][c1][r2][c2][v][2] = nv == k;
  }
  
  int res = 0;
  for (int c = c2, nv = v; c >= c1; --c) {
    nv = nxt[nv][s[r2][c] - 'A'];
    res += DT(r1, c, r2 - 1, c2, nv);
  }
  return dp[r1][c1][r2][c2][v][2] = res;
}

int DT(int r1, int c1, int r2, int c2, int v) {
  if (~dp[r1][c1][r2][c2][v][3]) return dp[r1][c1][r2][c2][v][3];
  
  if (c1 == c2) {
    int nv = v;
    for (int r = r2; r >= r1; --r) 
      nv = nxt[nv][s[r][c1] - 'A'];
    return dp[r1][c1][r2][c2][v][3] = nv == k;
  }
  
  int res = 0;
  for (int r = r2, nv = v; r >= r1; --r) {
    nv = nxt[nv][s[r][c1] - 'A'];
    res += TT(r, c1 + 1, r2, c2, nv);
  }
  return dp[r1][c1][r2][c2][v][3] = res;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> t;
  for (int i = 0; i < n; ++i)
    cin >> s[i];
  
  k = t.size(); t = '#' + t; 
  for (int i = 2, j = 0; i <= k; ++i) {
    while (j > 0 && t[i] != t[j + 1]) j = p[j];
    if (t[i] == t[j + 1]) j++;
    p[i] = j;
  }
  
  for (int i = 0; i <= k - 1; ++i) for (int c = 0; c < 26; ++c) 
    if (c + 'A' != t[i + 1]) nxt[i][c] = nxt[p[i]][c];
    else nxt[i][c] = i + 1;
  
  
  for (int c = 0; c < 26; ++c) nxt[k][c] = k;
  
  
  memset(dp, -1, sizeof(dp));
  cout << TT(0, 0, n - 1, m - 1, 0);
	return 0;
}

