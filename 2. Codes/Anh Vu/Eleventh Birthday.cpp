#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005, M = 998244353;
int a[N], b[N], dp1[N][N][11], dp2[N][N][11];
int n, m, k;

void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

ll fac[N];

int digitCount(int x) {
  int cnt = 0;
  while (x) x /= 10, cnt++;
  return cnt;
}

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll C(int n, int k) {
  return fac[n] * pw(fac[k], M - 2) % M * pw(fac[n - k], M - 2) % M;
}

ll euler(int n, int m) {
  if (n == 0) return m == 0;
  return C(n + m - 1, n - 1) * fac[m] % M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  fac[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = fac[i - 1] * i % M;
  
  int T; cin >> T;
  while (T--) {
    cin >> k; n = 0, m = 0;
    for (int i = 1, x; i <= k; ++i) {
      cin >> x;
      if (digitCount(x) % 2 == 1) a[++n] = x;
      else b[++m] = x;
    }
    
    for (int i = 0; i <= k; ++i) for (int j = 0; j <= k; ++j) for (int t = 0; t < 11; ++t)
      dp1[i][j][t] = dp2[i][j][t] = 0;
    
    dp1[0][0][0] = 1; int tot = (n + 1) / 2;
    for (int i = 0; i < n; ++i) {
      int le = 0, chan = 0;
      vector<int> nums;
      while (a[i + 1]) nums.emplace_back(a[i + 1] % 10), a[i + 1] /= 10;
      reverse(nums.begin(), nums.end());
      for (int i = 0; i < nums.size(); ++i) {
        if (i % 2 == 0) le = (le + nums[i]) % 11, chan = (chan - nums[i] + 11) % 11;
        else chan = (chan + nums[i]) % 11, le = (le - nums[i] + 11) % 11;
      }
      
      for (int j = 0; j <= tot; ++j) for (int t = 0; t < 11; ++t) {
        if (!dp1[i][j][t]) continue;
        // bo vao vi tri le
        add(dp1[i + 1][j + 1][(t + le) % 11], dp1[i][j][t]);
        // bo vao vi tri chan
        add(dp1[i + 1][j][(t + chan) % 11], dp1[i][j][t]);
      }
    } 
    for (int t = 0; t < 11; ++t) 
      dp2[0][0][t] = 1LL * dp1[n][tot][t] * fac[tot] % M * fac[n - tot] % M;
    for (int i = 0; i < m; ++i) {
      int le = 0, chan = 0;
      vector<int> nums; 
      while (b[i + 1]) nums.emplace_back(b[i + 1] % 10), b[i + 1] /= 10;
      reverse(nums.begin(), nums.end());
      for (int i = 0; i < nums.size(); ++i) {
        if (i % 2 == 0) le = (le + nums[i]) % 11, chan = (chan - nums[i] + 11) % 11;
        else chan = (chan + nums[i]) % 11, le = (le - nums[i] + 11) % 11;
      }
      
      for (int j = 0; j <= i; ++j) for (int t = 0; t < 11; ++t) {
        if (!dp2[i][j][t]) continue;
        // bo vao vi tri le
        add(dp2[i + 1][j + 1][(t + le) % 11], dp2[i][j][t]);
        // bo vao vi tri chan
        add(dp2[i + 1][j][(t + chan) % 11], dp2[i][j][t]);
      }
    }
    int res = 0;
    for (int j = 0; j <= m; ++j) if (dp2[m][j][0])
      add(res, 1LL * dp2[m][j][0] * euler((n/2+1), j) % M * euler((n+1)/2, m-j) % M);
    cout << res << '\n';
  }

	return 0;
}

