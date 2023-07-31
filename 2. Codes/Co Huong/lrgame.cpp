#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 55;
int vis[N][N][N][3];
string dp[N][N][N][3], a, b;
//code xau vai lon
string call(int i, int l, int r, int t) {
  if (vis[i][l][r][t]) return dp[i][l][r][t];
  string res = string(51, '~');
  // dat a[i] vao b[l] 
  if (t == 0) {
    if (i == 0) return a[i] >= b[l] ? string(1, a[i]) : "~";
    // >=
    if (a[i] > b[l]) res = min(res, a[i] + call(i - 1, l + 1, r, 2));
    else if (a[i] == b[l]) res = min(res, a[i] + call(i - 1, l + 1, r, 0));
    
    if (a[i] >= b[r]) res = min(res, call(i - 1, l, r - 1, 0) + a[i]);
    else res = min(res, call(i - 1, l, r - 1, 1) + a[i]);

  } else if (t == 1) {
    if (i == 0) return a[i] > b[l] ? string(1, a[i]) : "~";
    // >
    if (a[i] > b[l]) res = min(res, a[i] + call(i - 1, l + 1, r, 2));
    else if (a[i] == b[l]) res = min(res, a[i] + call(i - 1, l + 1, r, 1));
    
    if (a[i] > b[r]) res = min(res, call(i - 1, l, r - 1, 0) + a[i]);
    else res = min(res, call(i - 1, l, r - 1, 1) + a[i]);
  
  } else {
    if (i == 0) return string(1, a[i]);
    // bat ki
    res = min(a[i] + call(i - 1, l + 1, r, 2), call(i - 1, l, r - 1, 2) + a[i]);
  }
  //if (t != 2) cerr << i << ' ' << l << ' ' << r << ' ' << t << ' ' << res << '\n';

  return vis[i][l][r][t] = 1, dp[i][l][r][t] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("lrgame.inp", "r"))
    freopen("lrgame.inp", "r", stdin),
    freopen("lrgame.out", "w", stdout);
  cin >> a >> b; int n = a.size();
  auto res = call(n - 1, 0, n - 1, 0);
  //if (res.size() > a.size()) res = "-1";
  cout << res;
	return 0;
}

