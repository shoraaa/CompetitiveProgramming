#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1005;
int dp[N][N];
string s, t;

int call(int l, int r) {
  if (-dp[l][r]) return dp[l][r];
  if (l == r) return 0;
  if (l <= r) return dp[l][r] = (t[r] == 'A' && call(l, r - 1)) | (t[l] == 'B' && call(r, l + 1));
  return dp[l][r] = (t[r] == 'A' && call(l, r + 1)) | (t[l] == 'B' && call(r, l - 1));
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("abba.inp", "r"))
    freopen("abba.inp", "r", stdin),
    freopen("abba.out", "w", stdout);
  while (cin >> s >> t) {
    memset(dp, -1, sizeof(dp));
    int flag = 0; 
    for (int i = 0; i < t.size() - s.size() + 1; ++i) {
      if (t.substr(i, s.size()) == s) dp[i][i + s.size() - 1] = 1, flag = 1;
    }
    for (int i = s.size() - 1; i < t.size(); ++i) {
      string tmp;
      for (int j = i; j >= i - int(s.size()) + 1; --j) tmp += t[j];
      if (tmp == s) dp[i][i - int(s.size()) + 1] = 1, flag = 1;
    }
    if (!flag) {
      cout << "No\n"; continue;
    }
    cout << (call(0, t.size()-1) ? "Yes\n" : "No\n");
    
  }
	return 0;
}
