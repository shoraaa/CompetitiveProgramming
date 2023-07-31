#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
pair<int, int> a[N];
vector<int> pos;
vector<int> st[N];
#define fi first
#define se second
int n, k, m;

int bit[N];
void update(int i) {
  for (i++; i; i -= i & -i)
    bit[i]++;
}
int get(int i) {
  int res = 0; 
  for (i++; i <= m; i += i & -i)
    res += bit[i];
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0, l, r; i < n; ++i)
    cin >> l >> r, a[i] = {l, r},
    pos.emplace_back(l), pos.emplace_back(r);
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos.begin(), pos.end()), pos.end());
  m = pos.size();
  for (int i = 0; i < n; ++i)
    st[lower_bound(pos.begin(), pos.end(), a[i].fi) - pos.begin()].emplace_back(
       lower_bound(pos.begin(), pos.end(), a[i].se) - pos.begin());
  int res = 0;
  for (int i = 0, j = 0; i < m; ++i) {
    for (int r : st[i]) update(r);
    if (j < i) j = i;
    while (j < m && get(j) >= k) j++;
    j--; if (j >= i) res = max(res, pos[j] - pos[i]);
  }
  cout << res;
	return 0;
}

