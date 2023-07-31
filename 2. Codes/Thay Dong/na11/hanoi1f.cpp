#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int g[3][3];
char ch[3];
#define fi first
#define se second
vector<pair<int, int>> res;

void task1(int n, int c1, int c2, int c3) {
  if (n == 0) return;
  if (g[c1][c2]) {
    task1(n - 1, c1, c3, c2);
    res.emplace_back(c1, c2);
    task1(n - 1, c3, c2, c1);
  } else {
    task1(n - 1, c1, c2, c3);
    res.emplace_back(c1, c3);
    task1(n - 1, c2, c1, c3);
    res.emplace_back(c3, c2);
    task1(n - 1, c1, c2, c3);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n; cin >> n; ch[0] = 'A', ch[1] = 'B', ch[2] = 'C';
  for (int i = 0; i < 3; ++i) 
    for (int j = 0; j < 3; ++j)
      cin >> g[i][j];
  res.reserve(20000000);
  task1(n, 0, 2, 1);
  cout << res.size() << '\n';
  for (auto& p : res)
    cout << ch[p.fi] << ch[p.se] << '\n';
	return 0;
}

