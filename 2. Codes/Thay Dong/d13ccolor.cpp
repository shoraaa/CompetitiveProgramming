#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 50 + 5;
int a[N][N], b[N][N], cnt[N];
int n, m;
#define ii pair<int, int>
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        cin >> a[i][j], cnt[a[i][j]]++;
    set<pair<int, int>> s;
    for (int i = 1; i <= m; ++i)
      if (cnt[i]) s.insert({cnt[i], i});
    for (int i = 0; i < m; ++i) {
      auto mn = *s.begin(), mx = *(--s.end());
      s.erase(mn), s.erase(mx);
      for (int r = 0; r < n; ++r) 
        if (mn.first) b[r][i] = mn.second, mn.first--;
        else b[r][i] = mx.second, mx.first--;
      if (mn.first) s.insert(mn);
      if (mx.first) s.insert(mx);
    }
    vector<pair<ii, ii>> res;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (a[i][j] != b[i][j]) {
      for (int r = i; r < n; ++r) for (int c = r==i?j+1:0; c < m; ++c) if (a[r][c] == b[i][j]) {
        res.emplace_back(ii(i, j), ii(r, c)); 
        swap(a[i][j], a[r][c]); break;
      }
    }
    cout << res.size() << '\n';
    for (auto& p : res)
      cout << p.first.first+1 << ' ' << p.first.second+1 << ' ' 
           << p.second.first+1 << ' ' << p.second.second+1 << '\n';
  }
	return 0;
}

