#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
string s; int n;
int vis[256];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> s;
    n = s.size();
    memset(vis, 0, sizeof(vis));
    int res = 0;
    for (char c : s) {
      res += !vis[c];
      vis[c] = 1;
    }
    cout << res << '\n';
  }
	return 0;
}

