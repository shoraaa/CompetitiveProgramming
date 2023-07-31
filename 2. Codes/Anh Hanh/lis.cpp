#include <bits/stdc++.h>
#define print(_v) for (auto &_ : _v) {cerr << _ << ' ';} cerr << endl;
using namespace std;
using ll = long long;
void file() {
  const string FILE_NAME = "lis";
  freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
  freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int oo = 1e9;
const int N = 220797 + 5;
struct bit_prefix {
	vector<int> bit;
	int n;
	bit_prefix(int n): n(n), bit(n + 5) {}
	int get(int i) {
		int res = 0;
		for (; i; i -= i & -i)
			res = max(res, bit[i]);
		return res;
	}
	void update(int i, int v) {
		for (; i <= n; i += i & -i)
			bit[i] = max(bit[i], v);
	}
	void clear() {
		vector<int>(n + 5).swap(bit);
	}
};
struct bit_suffix {
	vector<int> bit;
	int n;
	bit_suffix(int n): n(n), bit(n + 5) {}
	int get(int i) {
		int res = 0;
		for (; i <= n; i += i & -i)
			res = max(res, bit[i]);
		return res;
	}
	void update(int i, int v) {
		for (; i; i -= i & -i)
			bit[i] = max(bit[i], v);
	}
	void clear() {
		vector<int>(n + 5).swap(bit);
	}
};
int a[N], b[N], dp[3][N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  file();
  cin >> n;
  vector<int> c(n * 2);
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = a[i], c[i + n] = -a[i];
  sort(c.begin(), c.end());
  c.erase(unique(c.begin(), c.end()), c.end());
  int m = c.size(); 
  bit_prefix bit_0(m), bit_1(m), bit_2(m);
  for (int i = 0; i < n; ++i) {
		int x = a[i];
  	a[i] = lower_bound(c.begin(), c.end(), x) - c.begin() + 1,
		b[i] = lower_bound(c.begin(), c.end(), -x) - c.begin() + 1;
	}
  // dp[i][j] la day dai nhat ma thang i thuoc nhom thu j
  // neu j le thi dp[i][j] = max(dp[k][j]) + 1 : k < i, a[k] < a[i] hoac dp[i][j] = dp[i][j-1]
  // neu j chan thi dp[i][j] = max(dp[k][j]) + 1 : k < i, a[k] > a[i] hoac dp[i][j] = dp[i][j-1]
  int res = 1;
  for (int i = 0; i < n; ++i) 
  	dp[0][i] = bit_0.get(a[i] - 1) + 1,
  	bit_0.update(a[i], dp[0][i]),
		res = max(res, dp[0][i]);
  bit_0.clear();
  for (int i = 0; i < n; ++i) {
  	dp[1][i] = max(bit_0.get(b[i] - 1), bit_1.get(b[i] - 1)) + 1,
  	bit_0.update(a[i], dp[0][i]),
		bit_1.update(b[i], dp[1][i]);
		res = max(res, dp[1][i]);
	}
	bit_1.clear();
	for (int i = 0; i < n; ++i) {
  	dp[2][i] = max(bit_1.get(a[i] - 1), bit_2.get(a[i] - 1)) + 1,
  	bit_1.update(b[i], dp[1][i]),
		bit_2.update(a[i], dp[2][i]);
		res = max(res, dp[2][i]);
	}
  cout << res;
  return 0;
}
