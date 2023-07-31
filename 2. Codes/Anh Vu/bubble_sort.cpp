#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, Q = 1e6 + 5, K = 100;
int a[N], p[N];
int n, k, q;
vector<int> pos[N];

int bit[N];
void add(int i) {
  for (; i <= k; i += i & -i)
    bit[i]++;
}
int get(int i) {
  int res = 0;
  for (; i; i -= i & -i)
    res += bit[i];
  return res;
}

ll val[N], delta[Q];
vector<pair<int, int>> que[N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> q;
  for (int i = 0; i < n; ++i)
    cin >> a[i], pos[a[i]].emplace_back(i);
  for (int i = 0; i < n; ++i)
    p[i] = i + 1;
  for (int i = 1, j; i <= q; ++i) {
    cin >> j, j--;
    int x = p[j + 1], y = p[j];
    if (pos[x].size() > K) que[x].emplace_back(y, i);
    else if (pos[y].size() > K) que[y].emplace_back(x, -i);
    else {
      ll xy = 0;
      for (int i = 0, j = 0; j < pos[y].size(); ++j) {
        while (i < pos[x].size() && pos[x][i] < pos[y][j]) i++;
        xy += i;
      }
      ll yx = ll(pos[x].size()) * pos[y].size() - xy;
      delta[i] = -xy + yx;
    }
    swap(p[j + 1], p[j]);
  }
  for (int x = 1; x <= k; ++x) if (pos[x].size() > K) {
    for (int y = 1; y <= k; ++y) val[y] = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) 
      if (a[i] == x) cnt++;
      else val[a[i]] += cnt;
    for (auto& qr : que[x]) {
      int y = qr.first, i = qr.second;
      ll xy = val[y], yx = ll(pos[x].size()) * pos[y].size() - xy;
      if (i > 0) delta[i] = -xy + yx;
      else delta[-i] = -yx + xy;
    } 
  }
  ll res = 0;
  for (int i = n-1; ~i; --i) 
    res += get(a[i] - 1), add(a[i]);
  for (int i = 1; i <= q; ++i) {
    res += delta[i]; cout << res << '\n';
  }
	return 0;
}

