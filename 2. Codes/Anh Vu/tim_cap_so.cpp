#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 5;
int a[N], L[N], R[N];
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  stack<int> st;
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.top()] % a[i] == 0) st.pop();
    L[i] = st.empty() ? 0 : st.top() + 1;
    st.push(i);
  }
  st = stack<int>();
  for (int i = n-1; ~i; --i) {
    while (!st.empty() && a[st.top()] % a[i] == 0) st.pop();
    R[i] = st.empty() ? n-1 : st.top() - 1;
    st.push(i);
  }
  ll len = 0; vector<int> l;
  for (int i = 0; i < n; ++i) {
    if (R[i] - L[i] > len)
      len = R[i] - L[i], l = { L[i] };
    else if (R[i] - L[i] == len)
      l.emplace_back(L[i]);
  }
  sort(l.begin(), l.end());
  l.erase(unique(l.begin(), l.end()), l.end());
  cout << l.size() << ' ' << len << '\n';
  for (int i : l) cout << i+1 << ' ';
	return 0;
}

