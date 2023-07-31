#include<bits/stdc++.h>
using namespace std;
 
const int N = 1e5 + 5;
int a[N];
int n;
 
multiset<int> s;
void fix(int x) {
  int c = s.count(x);
  if (c == 1) {
    if (s.count(x - 1)) {
      s.erase(x - 1);
      s.erase(x);
      s.insert(x + 1);
      fix(x + 1);
      return;
    }
 
    if (s.count(x + 1)) {
      s.erase(x + 1);
      s.erase(x);
      s.insert(x + 2);
      fix(x + 2);
    }
 
    return;
 
  }
  // c == 2
  if (x == 1) {
    s.erase(x);
    s.insert(x + 1);
    fix(x + 1);
    return;
  }
 
  if (s.count(x + 1)) {
    s.erase(s.find(x));
    s.erase(x + 1);
    s.insert(x + 2);
    fix(x + 2);
    return;
  }
 
  if (s.count(x - 1)) {
    s.erase(s.find(x));
    s.erase(x - 1);
    s.insert(x + 1);
    fix(x + 1);
    return;
  }
 
  if (x == 2) {
    s.erase(x);
    s.insert(x - 1);
    s.insert(x + 1);
    fix(x - 1);
    fix(x + 1);
  } else {
    s.erase(x);
    s.insert(x - 2);
    s.insert(x + 1);
    fix(x - 2);
    fix(x + 1);
  }
 
}
const int M = 1e9 + 7;
 
int b[N];
long long dp[N][2];
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  // freopen("in", "r", stdin);
 
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
 
  for (int i = 1; i <= n; ++i) {
    s.insert(a[i]);
    fix(a[i]);
 
    int m = 0;
    for (int x : s) b[++m] = x;
 
 
//    for (int i = 1; i <= m; ++i) {
//      cerr << b[i] << " \n"[i == m];
//    }
 
 
    dp[1][0] = 1;
    dp[1][1] = (b[1] - 1) / 2;
    for (int i = 2; i <= m; ++i) {
      int len = b[i] - b[i - 1];
      if (len & 1) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % M;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) * (len / 2) % M;
      } else {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % M;
        dp[i][1] = (dp[i - 1][0] * (len / 2 - 1) % M) +
              (dp[i - 1][1] * (len / 2) % M) % M;
      }
    }
    cout << (dp[m][0] + dp[m][1]) % M << '\n';
 
  }
 
  return 0;
}