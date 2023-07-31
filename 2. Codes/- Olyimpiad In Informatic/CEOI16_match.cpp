#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
string s;
int n;

char ans[N];

int good(stack<char> st, int i, int j = n) {
  for (; i <= j; ++i) {
    if (st.empty() || st.top() != s[i]) {
      st.push(s[i]);
    } else {
      st.pop();
    }
  }
  return st.empty();
}

void task1() {
  stack<char> st;
  for (int i = 1; i <= n; ++i) {
    if (st.empty() || st.top() != s[i]) {
      st.push(s[i]);
      ans[i] = '(';
    } else {
      st.push(s[i]);
      ans[i] = '(';
      if (good(st, i + 1)) continue;
      st.pop();
      ans[i] = ')';
      st.pop();
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << ans[i];
  }
  exit(0);
  
}

int last[N][26];

void solve(int l, int r) {
  if (l > r) return;
  int m = last[r][s[l] - 'a'];
  if (!m) {
    cout << -1;
    exit(0);
  }
  ans[l] = '(';
  ans[m] = ')';
  solve(l + 1, m - 1);
  solve(m + 1, r);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s;
  n = s.size();
  s = ' ' + s;
  
  // if (!good(stack<char>(), 1)) {
    // cout << -1;
    // return 0;
  // }
  
  // if (n <= 2000) task1();

  // last[i][c] = max j sao cho [j + 1..i] tm va s[j] = c
  for (int i = 1; i <= n; ++i) {
    last[i][s[i] - 'a'] = i;
    
    if (last[i - 1][s[i] - 'a']) {
      int j = last[i - 1][s[i] - 'a'] - 1;
      for (int c = 0; c < 26; ++c) if (!last[i][c]) {
        last[i][c] = last[j][c];
      }
    }
  }
  solve(1, n);

  for (int i = 1; i <= n; ++i) {
    cout << ans[i];
  }
  
	return 0;
}

