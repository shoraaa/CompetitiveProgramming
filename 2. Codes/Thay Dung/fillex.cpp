#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4e6 + 5;
int id = 0, lef[N], rig[N], siz[N], mn[N], mx[N];
bitset<N> is_min;
string s;
int n;

void dfs(int u) {
  if (!lef[u]) return siz[u] = mn[u] = mx[u] = 1, void();
  dfs(lef[u]), dfs(rig[u]);
  siz[u] = siz[lef[u]] + siz[rig[u]];
  if (is_min[u]) {
    mn[u] = min(mn[lef[u]], mn[rig[u]]);
    mx[u] = mx[lef[u]] + mx[rig[u]];
  } else {
    mn[u] = mn[lef[u]] + mn[rig[u]];
    mx[u] = min(mx[lef[u]], mx[rig[u]]);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s; n = s.size();
  stack<int> st; st.push(0);
  for (int i = 3; i < n; ++i) {
    if (s[i] == '(' || s[i] == '?') {
      int v = ++id; is_min[v] = s[i-1] == 'n';
      if (!lef[st.top()]) lef[st.top()] = v;
      else rig[st.top()] = v;
      if (s[i] == '(') st.push(v);
    } else if (s[i] == ')') {
      st.pop();
    }
  }
  dfs(1);
  cout << (siz[1]-mx[1]+1) - mn[1] + 1;
	return 0;
}

