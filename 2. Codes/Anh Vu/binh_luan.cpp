#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
int a[N];
int n, cnt = 0;
ll c, r;
int sign(int x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}
int get(int l, int r) {
  if (l == -1 || r == n) return 0;
  int len = r - l - 1;
  return (len & 1) ^ (sign(a[l]) == sign(a[r]));
}
ll fuck_zero() {
  vector<int> tmp;
  ll res = 0;
  for (int i = 0; i < n; ++i)
    if (a[i] == 0) res += r;
    else tmp.emplace_back(a[i]);
  for (int i = 0; i < tmp.size();) {
    int j = i + 1;
    while (j < tmp.size() && sign(tmp[i]) == sign(tmp[j])) res += r, j++;
    i = j;
  }
  return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> c >> r;
  vector<int> idx(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i], idx[i] = i;
  sort(idx.begin(), idx.end(), [&](int u, int v) {
    return abs(a[u]) > abs(a[v]);
  });
  ll res = fuck_zero();
  set<int> s = {-1, n};  
  for (int i : idx) {    
    res = min(res, c * (abs(a[i]) + 1) + r * cnt);
    if (a[i] == 0) break;
    auto it = s.lower_bound(i); 
    int r = *it; it--; int l = *it;
    cnt += get(l, i) + get(i, r) - get(l, r);
    s.insert(i);
  }
  cout << res;
	return 0;
}

