#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int nxt[N][30];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("slom.inp", "r")) 
    freopen("slom.inp", "r", stdin),
    freopen("slom.out", "w", stdout);
  int n, k; string s;
  cin >> k >> s; n = s.size();
  string t = s;
  for (int i = 0; i < n; ++i)
    nxt[i][0] = i & 1 ? -(i+1)/2+n : i/2;
  for (int j = 1; j < 30; ++j)
    for (int i = 0; i < n; ++i)
      nxt[i][j] = nxt[nxt[i][j-1]][j-1];
  for (int i = 0; i < n; ++i) {
    int cur = i;
    for (int j = 29; ~j; --j) if (k >> j & 1) cur = nxt[cur][j];
    t[cur] = s[i];
  }
  cout << t;
	return 0;
}

