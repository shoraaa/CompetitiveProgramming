#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5, inf = 1e9;
const int M = 998244353;
int mul(ll x, ll y) {
  return x * y % M;
}
int dif(int x, int y) {
  x -= y; if (x < 0) x += M; return x;
}
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int a[N], f[N][2], g[N][2];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  stack<int> st; 
  int f0 = 0, f1 = 0;
  f[0][0] = g[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    while (!st.empty() && a[st.top()] >= a[i]) {
      int r = st.top(); st.pop();
      sub(f0, mul(a[r], dif(g[r-1][1], st.empty() ? 0 : g[st.top()-1][1]))), 
      sub(f1, mul(a[r], dif(g[r-1][0], st.empty() ? 0 : g[st.top()-1][0])));
    }
    add(f0, mul(a[i], dif(g[i-1][1], st.empty() ? 0 : g[st.top()-1][1]))), 
    add(f1, mul(a[i], dif(g[i-1][0], st.empty() ? 0 : g[st.top()-1][0])));
    st.push(i);
    f[i][0] = g[i][0] = f0, f[i][1] = g[i][1] = f1;
    add(g[i][0], g[i-1][0]), add(g[i][1], g[i-1][1]);
  }
  cout << dif(f[n][n&1], f[n][(n-1)&1]);
	return 0;
}

