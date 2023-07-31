#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, oo = 1e9;
int a[N], pre[N], nxt[N], high[N][20], low[N][20];
pair<int, int> spt[N][20];
int n, q;
int jump(int i, int j) {
  int res = 0; 
  for (int k = 19; ~k; --k) if (a[high[i][k]] <= a[j]) 
    i = high[i][k], res += 1 << k;
  for (int k = 19; ~k; --k) if (a[low[i][k]] <= a[j]) 
    i = low[i][k], res += 1 << k;
  return res;
}
int max_position(int l, int r) {
  if (l > r) return n+2;
  int k = __lg(r-l+1);
  return max(spt[l][k], spt[r-(1<<k)+1][k]).second;
}
int longest_suffix(int l1, int r1, int l2, int r2) {
  int max_val = a[max_position(l2, r2)];
  int lo = l1, hi = r1, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (a[max_position(mid, l2-1)] < max_val)
      ans = mid, hi = mid - 1;
    else
      lo = mid + 1;
  }
  return ans;
}
stack<int> st;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q; a[0] = a[n+1] = 1e9;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], spt[i][0] = {a[i], i};
  for (int k = 1; k < 20; ++k)
    for (int i = 1; i + (1 << k) - 1 <= n; ++i)
      spt[i][k] = max(spt[i][k-1], spt[i+(1<<(k-1))][k-1]);
  st.emplace(0); 
  for (int i = 1; i <= n; ++i) {
    while (!st.empty() && a[st.top()] < a[i]) st.pop();
    pre[i] = st.top(); st.push(i);
  }
  while (!st.empty()) st.pop(); 
  st.emplace(n+1);
  for (int i = n; i; --i) {
    while (!st.empty() && a[st.top()] < a[i]) st.pop();
    nxt[i] = st.top(); st.push(i);
  }
  for (int i = 1; i <= n; ++i)
    if (a[nxt[i]] > a[pre[i]]) high[i][0] = nxt[i], low[i][0] = pre[i];
    else high[i][0] = pre[i], low[i][0] = nxt[i];
  for (int k = 1; k < 20; ++k)
    for (int i = 1; i <= n; ++i)
      high[i][k] = high[high[i][k-1]][k-1],
      low[i][k] = low[low[i][k-1]][k-1];
  for (int i = 0, l1, r1, l2, r2; i < q; ++i) {
    cin >> l1 >> r1 >> l2 >> r2, l1++, r1++, l2++, r2++;
    l1 = longest_suffix(l1, r1, l2, r2);
    if (!~l1) { cout << -1 << '\n'; continue; }
    int m1 = max_position(l1, r1), m2 = max_position(l2, r2),
        m3 = max_position(l1, l2-1), m4 = pre[m3];
    cout << min(jump(m1, m3), a[m4] < a[m2] ? jump(m1, m4) : oo) + 1 << '\n';
  }
	return 0;
}

