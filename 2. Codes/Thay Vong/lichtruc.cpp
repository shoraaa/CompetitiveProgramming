#include<bits/stdc++.h>
using namespace std;
void file() {
	const string FILE_NAME = "lichtruc";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
using ll = long long;
const int N = 1e5 + 5;
pair<int, int> a[N * 2];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n;
  for (int i = 0, l, r; i < n; ++i)
    cin >> l >> r,
    a[i] = {l, 1}, a[i + n] = {r + 1, -1};
  sort(a, a + n * 2);
  int cur = 0, res = 0;
  for (int i = 0; i < n * 2;) {
    int j = i;
    while (j < n * 2 && a[j].first == a[i].first)
      cur += a[j].second, j++;
    res = max(res, cur); i = j;
  }
  cout << res;
	return 0;
}

