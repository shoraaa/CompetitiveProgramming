#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
map<pair<int, int>, bool> adj;
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, l, r; i < m; ++i) {
    cin >> l >> r;
    if (l > r) swap(l, r);
    adj[{l, r}] = 1;
  }
  int res = 1;
  for (int i = 1; i <= n - 1; ++i) {
    int j = 0;
    for (;; ++j) {
      if (!adj[{i - j, i + j + 1}]) break;
    }
    res = max(res, j * 2);
  }
  for (int i = 2; i <= n - 1; ++i) {
    int j = 0;
    for (;; ++j) {
      if (!adj[{i - j - 1, i + j + 1}]) break;
    }
    res = max(res, j * 2 + 1);
  }
  cout << res;
	return 0;
}

