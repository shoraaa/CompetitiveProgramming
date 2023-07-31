#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 5;
const ll INF = 1e18;
vector<ll> dp[N];
int a[N];
int n, k;

pair<int, int> spt[N][14];
int get(int l, int r) {
  int k = __lg(r - l + 1);
  return max(spt[l][k], spt[r - (1 << k) + 1][k]).second;
}

int solve(int l, int r) {
  if (l > r) return -1; 
  int m = get(l, r), n = r - l + 1;
  
  dp[m].resize(n + 1, INF);
  if (l == r) return dp[l][0] = 0, dp[l][1] = a[l], l;
  
  dp[m][0] = 0;
  int u = solve(l, m - 1), v = solve(m + 1, r);
  
  if (u == -1 || v == -1) {
    int c = u == -1 ? v : u;
    for (int i = 1; i <= n; ++i) 
      dp[m][i] = min(i <= n - 1 ? dp[c][i] : INF, dp[c][i - 1] + ll(a[m]) * i);
    return m;
  } 
  
  int n1 = m - l, n2 = r - m;
  
  for (int i = 0; i <= n; ++i) {
    for (int j = max(0, i - n2); j <= min(n1, i); ++j) {
      dp[m][i] = min(dp[m][i], dp[u][j] + dp[v][i - j] + ll(a[m]) * j * (i - j));
    }
  }
  
  for (int i = 0; i < n; ++i)
    dp[m][i + 1] = min(dp[m][i + 1], dp[m][i] + ll(a[m]) * (i + 1));
  
  return m;
  
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i], spt[i][0].first = a[i], spt[i][0].second = i;
  for (int j = 1; j < 14; ++j) for (int i = 0; i + (1 << j) - 1 < n; ++i)
    spt[i][j] = max(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
    
  int u = solve(0, n - 1);
  cout << dp[u][k];
	return 0;
}
