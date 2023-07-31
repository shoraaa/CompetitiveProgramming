#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5;
bitset<N> st[N * 2];
vector<int> seq[N];
int x, y, v;
void add(int k, int l, int r) {
  if (l > y || r < x) return;
  if (l >= x && r <= y)
    return seq[k].emplace_back(v), void();
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  add(lc, l, m), add(rc, m+1, r);
}
bitset<N> res;
void dfs(int k, int l, int r, bitset<N>& cur) {
  bitset<N> bit = cur;
  for (int v : seq[k])
    bit |= bit << v;
  if (l == r)
    return res |= bit, void();
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  dfs(lc, l, m, bit), dfs(rc, m+1, r, bit);
}
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  for (int i = 0; i < q; ++i)
    cin >> x >> y >> v, x--, y--,
    add(1, 0, n-1);
  bitset<N> cur;
  cur[0] = 1;
  dfs(1, 0, n-1, cur);
  vector<int> val;
  for (int i = 1; i <= n; ++i)
    if (res[i]) val.emplace_back(i);
  cout << val.size() << '\n';
  for (int v : val)
    cout << v << ' ';
	return 0;
}

