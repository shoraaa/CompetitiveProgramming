#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "intersect";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
vector<tuple<int, int, int>> a, b;
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n >> m;
  for (int i = 0, x1, x2, y; i < n; ++i)
    cin >> x1 >> x2 >> y,
    a.emplace_back(x1, x2, y);
  for (int i = 0, y1, y2, x; i < m; ++i)
    cin >> y1 >> y2 >> x,
    b.emplace_back(y1, y2, x);
  int res = 0;
  for (auto& p1 : a) for (auto& p2 : b) {
    int x1, x2, y; tie(x1, x2, y) = p1;
        int y1, y2, x; tie(y1, y2, x) = p2;
        res += x1 <= x && x <= x2 && y1 <= y && y <= y2;
  }
  cout << res;
	return 0;
}

