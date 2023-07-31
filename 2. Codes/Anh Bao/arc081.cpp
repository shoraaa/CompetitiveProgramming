#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2000 + 5;
int a[N][N], h[N-1], L[N-1], R[N-1];
int n, m;
void solve() {
  stack<int> st;
  for (int i = 0; i < m-1; ++i) {
    while (!st.empty() && h[st.top()] >= h[i]) st.pop();
    L[i] = st.empty() ? 0 : st.top() + 1;
    st.push(i);
  }
  st = stack<int>();
  for (int i = m-2; i >= 0; --i) {
    while (!st.empty() && h[st.top()] >= h[i]) st.pop();
    R[i] = st.empty() ? m-2 : st.top() - 1;
    st.push(i);
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; char c;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    cin >> c, a[i][j] = c == '#';
  int res = max(n, m);
  for (int j = 0; j < m-1; ++j) h[j] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < m-1; ++j)
      if (a[i][j] ^ a[i][j+1] == a[i-1][j] ^ a[i-1][j+1]) h[j]++;
      else h[j] = 1;
    solve();
    for (int j = 0; j < m-1; ++j)
      res = max(res, h[j] * (R[j] - L[j] + 2));
  }
  cout << res;
	return 0;
}

