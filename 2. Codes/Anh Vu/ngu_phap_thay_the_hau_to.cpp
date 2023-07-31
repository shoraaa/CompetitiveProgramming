#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
const int M = 20 + 5, N = 100 + 5;
int dis[M*(2*N+2)][M*(2*N+2)], inf;
vector<string> a; vector<int> b[M];
map<string, int> idx;
void add(string& s) {
  string suf;
  int m = s.size();
  for (int i = 0, k; i < m; ++i) {
    suf = s.substr(i, m - i), k = suf.size();
    if (!idx.count(suf)) {
      int id = idx.size();
      idx[suf] = id; 
      
      a.emplace_back(suf);
      b[k].emplace_back(id), 
      dis[id][id] = 0;
    }
  }
}
string s, t;
int n;
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	for (int tc = 1;; tc++) {
    cin >> s; if (s == ".") break;
    cin >> t >> n;
    memset(dis, 0x3f, sizeof(dis)), inf = dis[0][0];
    add(s), add(t);
    string x, y;
    for (int i = 0, k; i < n; ++i) {
      cin >> x >> y, k = x.size(); 
      add(x), add(y);
      dis[idx[x]][idx[y]] = min(dis[idx[x]][idx[y]], 1LL);
    }
    for (int m = 1; m <= s.size(); ++m) {
      if (m > 1) {
        for (int i : b[m]) for (int j : b[m]) {
          string x = a[i], y = a[j];
          if (x[0] == y[0]) {
            string nx = x.substr(1, m-1), ny = y.substr(1, m-1);
            dis[i][j] = min(dis[i][j], dis[idx[nx]][idx[ny]]);
          }
        }
      }
      for (int k : b[m]) for (int i : b[m]) for (int j : b[m])
        if (dis[i][k] + dis[k][j] < dis[i][j]) 
          dis[i][j] = dis[i][k] + dis[k][j];
    }
    int res = dis[idx[s]][idx[t]];
    cout << "Case " << tc << ": ";
    if (res == inf) cout << "No solution\n";
    else cout << res << '\n';
    
    for (int i = 1; i <= 20; ++i) 
      b[i].clear(); 
    a.clear(), idx.clear();
  }
	return 0;
}

