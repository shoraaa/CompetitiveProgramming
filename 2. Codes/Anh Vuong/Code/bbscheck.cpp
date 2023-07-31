#include<bits/stdc++.h>
using namespace std;
using ll = long long;

char open[256];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("bbscheck.in", "r"))  
    freopen("bbscheck.in", "r", stdin),
    freopen("bbscheck.out", "w", stdout);
  string s;
  cin >> s;
  open[')'] = '(';
  open[']'] = '[';
  open['}'] = '{';
  stack<char> st;
  int res = 0;
  for (auto& c : s) {
    if (c == '(' || c == '[' || c == '{') {
      st.push(c);
    } else {
      if (st.empty() || st.top() != open[c]) 
        return cout << 0, 0;
      res = max(res, (int)st.size()); st.pop(); 
    }
  }
  cout << res;
	return 0;
}

