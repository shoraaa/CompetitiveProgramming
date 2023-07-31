#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "lminmax";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e6 + 5, inf = 1e9;
int a[N];
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  deque<int> qmin, qmax;
  int res = 0;
  auto insert = [&](int i) {
    while (!qmin.empty() && a[i] <= a[qmin.back()]) qmin.pop_back();
    while (!qmax.empty() && a[i] >= a[qmax.back()]) qmax.pop_back();
    qmin.emplace_back(i), qmax.emplace_back(i);
  };
  auto check = [&](int i) {
    int mn = min(a[i], qmin.empty() ? inf : a[qmin.front()]),
        mx = max(a[i], qmax.empty() ? -inf : a[qmax.front()]);
    return int(mx - mn <= k);
  };
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && check(j)) insert(j), j++;
    res = max(res, j - i);
    if (qmin.front() == i) qmin.pop_front();
    if (qmax.front() == i) qmax.pop_front();
  }
  cout << res; 
	return 0;
}

