#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
int a[N], f[N], res[N], bit[N];
vector<pair<int, int>> lef[N];
int n, q;

int get(int i) {
  int res = 0;
  for (; i; i -= i & -i)
    res ^= bit[i];
  return res;
}
void update(int i, int x) {
  for (; i <= n; i += i & -i)
    bit[i] ^= x;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("sumxor.inp", "r"))
    freopen("sumxor.inp", "r", stdin),
    freopen("sumxor.out", "w", stdout);
  int T; cin >> T;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], f[i] = f[i - 1] ^ a[i];
  cin >> q;
  for (int i = 0, l, r; i < q; ++i)
    cin >> l >> r, lef[r].emplace_back(l, i);
  map<int, int> last;
  for (int i = 1; i <= n; ++i) {
    if (last[a[i]]) update(last[a[i]], a[i]);
    last[a[i]] = i; update(i, a[i]);
    for (auto& p : lef[i]) {
      int l, id; tie(l, id) = p;
      res[id] = f[i]^f[l-1]^get(i)^get(l-1); 
    }
  }
  for (int i = 0; i < q; ++i)
    cout << res[i] << ' ';
	return 0;
}

