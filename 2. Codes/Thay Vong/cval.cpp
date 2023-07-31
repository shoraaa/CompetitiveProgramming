#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N], c[N], lef[N], rig[N], pre[N];
vector<int> L[N], R[N];
int n, m, q; stack<int> suf[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("cval.inp", "r"))
    freopen("cval.inp", "r", stdin),
    freopen("cval.out", "w", stdout);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
      cin >> a[i], c[i] = a[i];
    for (int i = 0; i < n; ++i) 
      L[i].clear(), R[i].clear();
    for (int i = 0, l, r; i < q; ++i) 
      cin >> l >> r, l--, r--,
      L[l].emplace_back(r),
      R[r].emplace_back(l);
    sort(c, c + n);
    m = unique(c, c + n) - c;
    for (int i = 0; i < n; ++i)
      a[i] = lower_bound(c, c + m, a[i]) - c;
    
    multiset<int> st;
    for (int i = 0; i < n; ++i) {
      for (int r : L[i]) st.insert(i);
      lef[i] = st.empty() ? n : *st.begin();
      for (int l : R[i]) st.erase(st.find(l));
    }
    for (int i = n-1; ~i; --i) {
      for (int l : R[i]) st.insert(-i);
      rig[i] = st.empty() ? -1 : -*st.begin();
      for (int r : L[i]) st.erase(st.find(-r));
    }
    for (int i = 0; i < m; ++i)
      suf[i] = stack<int>();
    int j = -1; 
    for (int i = n-1; ~i; --i) {
      // not delete a[i] anymore
      if (!suf[a[i]].empty() && suf[a[i]].top() <= rig[i]) { j = i; break; }
      suf[a[i]].push(i);
    }
    if (j == -1) {
      cout << 0 << '\n'; continue;
    }
    int res = j + 1;
    for (int i = 0; i < m; ++i) pre[i] = -1;
    for (int i = 0; i < n; ++i) {
      // not delete a[i] anymore, increase j
      if (pre[a[i]] >= lef[i]) break;
      while (j+1 < n) {
        // delete j+1 until i satify
        if (suf[a[i]].empty() || suf[a[i]].top() > rig[i]) break;
        suf[a[j+1]].pop(); j++;
      }
      pre[a[i]] = i; res = min(res, j - i);
    }
    cout << res << '\n';
  }
	return 0;
}

