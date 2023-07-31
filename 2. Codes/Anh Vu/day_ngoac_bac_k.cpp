#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 1e9 + 7, N = 3e3 + 5;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M; 
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
int f[N][N], g[N][N], ans[N];
string s;
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s; n = s.size();
  s = ' ' + s; 
  // f[i][j] la dung i ki tu dau, j ki tu cuoi tao duoc bn palindrome do dai chan
  // g[i][j] la dung cac ki tu tu i den j tao duoc bn palindrome 
  // voi moi i j ma s[i] = s[j] ta co f[i-1][j+1] * g[i+1][j-1]
  for (int i = 1; i <= n; ++i) for (int j = n; j > i; --j) {
    add(f[i][j], f[i-1][j]);
    add(f[i][j], f[i][j+1]);
    sub(f[i][j], f[i-1][j+1]);
    if (s[i] == s[j]) 
      add(f[i][j], f[i-1][j+1] + 1);
  }
  
  for (int i = 1; i <= n; ++i)
    g[i][i] = 1;
  for (int l = 2; l <= n; ++l) for (int i = 1; i + l - 1 <= n; ++i) {
    int j = i + l - 1;
    add(g[i][j], g[i+1][j]);
    add(g[i][j], g[i][j-1]);
    sub(g[i][j], g[i+1][j-1]);
    if (s[i] == s[j])
      add(g[i][j], g[i+1][j-1] + 1);
  }
  for (int i = 1; i <= n; ++i)
    ans[i] = f[i-1][i+1] + 1;
  for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) if (s[i] == s[j]) {
    int val = mul(f[i-1][j+1] + 1, g[i+1][j-1] + 1);
    add(ans[i], val), add(ans[j], val);
  }
  int res = 0;
  for (int i = 1; i <= n; ++i)
    res ^= mul(ans[i], i);
  cout << res;  
	return 0;
}

