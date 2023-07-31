#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  const string FILE_NAME = "hindex";
  freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
  freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1 << 19 + 5;
struct S {
	int i, cnt; ll cost;
} a[N];
vector<int> t;
int n; ll b;
int check(int m) {
	auto cost = [&](S& p) {
		return max(0, m-p.cnt)*p.cost;
	};
	sort(a, a + n, [&](S& u, S& v) {
		return cost(u) < cost(v);
	});
	vector<int> tmp(n); ll cur = b;
	for (int i = 0; i < m; ++i) {
		cur -= cost(a[i]);
		if (cur < 0) return 0;
		tmp[a[i].i] = max(0, m - a[i].cnt);
	}
	t.swap(tmp);
	return 1;
}
int main() {
	//file();
  cin >> n >> b; t.resize(n);
  for (int i = 0; i < n; ++i)
		cin >> a[i].cnt;
	for (int i = 0; i < n; ++i)
		cin >> a[i].cost, a[i].i = i;
	int lo = 0, hi = n, mid, ans = 0;
	while (lo <= hi) {
		mid = lo + hi >> 1;
		if (check(mid))
			ans = mid,
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	cout << ans << '\n';
	for (int i = 0; i < n; ++i)
		cout << t[i] << ' ';
  return 0;
}


