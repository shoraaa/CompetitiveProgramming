#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 5, inf = 1e9;
int a[N][N], lef[N], rig[N], h[N];
ll dp[N][N];
int n, m, k;
ll solve(int c) {
  memset(h, 0, sizeof(h));
  h[0] = h[m+1] = -inf;
  ll res = 0;
  for (int d = 1; d <= n; ++d) {
    for (int i = 1; i <= m; ++i) 
      if (a[d][i] == c) h[i]++;
      else h[i] = 0;
    stack<int> st; st.push(0);
    for (int i = 1; i <= m; ++i) {
      while (h[st.top()] >= h[i]) st.pop();
      lef[i] = st.top() + 1; st.push(i);
    }
    st = stack<int>(); st.push(m+1);
    for (int i = m; i; --i) {
      while (h[st.top()] > h[i]) st.pop();
      rig[i] = st.top() - 1; st.push(i);
    }
    for (int i = 1; i <= m; ++i)
      res += dp[rig[i] - lef[i] + 1][h[i]],
      res -= dp[i - lef[i]][h[i]],
      res -= dp[rig[i] - i][h[i]];  
  }
  return res;
}
int len(int l, int r) {
  return max(0, r - l + 1);
}
int calc(int l, int r) {
  return len(l, r) * (len(l, r) + 1) / 2;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) 
    for (int j = 1; j <= m; ++j)
      cin >> a[i][j];
  for (int h = 1; h <= n; ++h) 
    for (int i = 1; i <= m; ++i) {
      // chon l, r <= i sao cho r >= [k/h] + l-1 
      // for (int l = 1; l <= i; ++l) {
        // dp[i][h] += len((k+h-1)/h + l-1, i);
      // }
      dp[i][h] = dp[i][h-1] + calc((k + h - 1) / h, i);
   }
  ll res = 0;
  for (int i = 1; i <= n; ++i)
    res += dp[m][i];
  res -= solve(0);
  res -= solve(1);
  cout << res << '\n';
	return 0;
}

