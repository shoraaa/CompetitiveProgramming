#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
pair<int, int> a[N], b[N];
#define r first
#define l second
int n;
int nxt[N][18];
vector<pair<int, int>> lef;

int get(int l, int r) {
  int i = lower_bound(lef.begin(), lef.end(), make_pair(l, -1)) - lef.begin(), res = 1;
  if (i == n || a[lef[i].second].r > r) return 0; i = lef[i].second;
  for (int j = 17; ~j; --j) if (nxt[i][j] != n && a[nxt[i][j]].r <= r)
    res += 1 << j, i = nxt[i][j];
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i].l >> a[i].r, b[i] = a[i];
  sort(a, a + n);
  for (int i = 0; i < n; ++i)
    lef.emplace_back(a[i].l, i);
  sort(lef.begin(), lef.end());
  for (int i = n-2; ~i; --i) lef[i].second = min(lef[i].second, lef[i+1].second);
  
  for (int i = 0; i <= n; ++i) nxt[i][0] = n;
  for (int i = n-1; ~i; --i) {
    int j = lower_bound(a, a + n, make_pair(a[i].l, -1)) - a;
    if (j == n || j == 0) continue;
    nxt[j - 1][0] = i;
  }
  for (int i = n-1; ~i; --i) nxt[i][0] = min(nxt[i][0], nxt[i+1][0]);
  
  for (int j = 1; j < 18; ++j)
    for (int i = 0; i <= n; ++i)
      nxt[i][j] = nxt[nxt[i][j-1]][j-1];

  set<pair<int, int>> s; s.insert({1e9, 1});
  vector<int> res;
  for (int i = 0; i < n; ++i) {
    auto it = s.upper_bound({b[i].r, -1});
    if (it == s.end() || it->l > b[i].l) continue;
    if (get(it->l, b[i].l - 1) + get(b[i].r + 1, it->r) + 1 == get(it->l, it->r)) {
      res.emplace_back(i);
      s.insert({b[i].l - 1, it->l}), s.insert({it->r, b[i].r + 1}), s.erase(it);
    }
  }
  cout << res.size() << '\n';
  for (int i : res) cout << i + 1 << ' ';
	return 0;
}

