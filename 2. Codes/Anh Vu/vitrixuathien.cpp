#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int n, m, q;
string s, t;
map<string, int> table;
bitset<N> idx[26];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  cin >> s;
  for (int i = 0; i < n; ++i)
    idx[s[i] - 'a'][i] = 1;
  for (int i = 0; i < q; ++i) {
    cin >> t; m = t.size();
    if (table.count(t)) {
      cout << table[t] << '\n';
      continue;
    }
    bitset<N> ans = idx[t[0] - 'a'];
    for (int i = 1; i < m; ++i)
      ans &= idx[t[i] - 'a'] >> i;
    int res = 0;
    for (int i = ans._Find_first(); i != N; i = ans._Find_next(i + m - 1))
      res++;
    cout << res << '\n';
    table[t] = res;
  }
	return 0;
}

