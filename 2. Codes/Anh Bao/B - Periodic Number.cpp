#include<bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> s; string res = "";
    for (int i = 1; i <= s.size() / 2; ++i) if (s.size() % i == 0) {
      auto t = s.substr(0, i), x = t;
      while (x.size() < s.size()) x += t;
      if (x <= s) res = max(res, x);
      
      t = to_string(stoll(t) - 1), x = t;
      while (x.size() < s.size()) x += t;
      if (x <= s) res = max(res, x);
      
    }
    if (res.empty() || res[0] == '0') cout << string(s.size() - 1, '9') << '\n';
    else cout << res << '\n';
  }
	return 0;
}

