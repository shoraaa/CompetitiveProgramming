#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 6005, M = 1e9 + 7;

void add(int& x, int y) {
  x += y; if (x >= M) x -= M; 
}
int mul(ll x, ll y) {
  return x * y % M;
}

int a[N], b[N];
int n;

int dp[N][N][2];
int get(string& s) {
  n = s.size();
  // dp[i][j][k] la xet den vi tri i, j thang ngoac mo duoc chon chua bi dong, k la co thang mo nao 
  // dang mo va bi bo qua hay ko
  // i mo -> bo vao dam chua bi dong
  // i dong -> chon trong dam chua dong
  dp[0][0][0] = 1;
  for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) for (int k = 0; k <= 1; ++k) {
    if (!dp[i][j][k]) continue;
    if (s[i] == '(') {
      add(dp[i + 1][j + 1][k], dp[i][j][k]);
      add(dp[i + 1][j][1], dp[i][j][k]);
    } else {
      // dong mot trong dong mo o truoc
      if (j != 0) add(dp[i + 1][j - 1][k], mul(dp[i][j][k], j));
      // bo qua thang dong nay, khi va chi khi ko co thang mo nao bi bo qua o truoc
      if (k == 0) add(dp[i + 1][j][k], dp[i][j][k]);
    }
  }
  int res = dp[n][0][0]; add(res, dp[n][0][1]);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i)
    cin >> b[i];
  sort(a, a + n);
  sort(b, b + n);
  string s;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && a[j] <= b[i]) s += '(', j++;
    s += ')'; 
  }
  cerr << s << '\n';
  cout << get(s);
	return 0;
}

