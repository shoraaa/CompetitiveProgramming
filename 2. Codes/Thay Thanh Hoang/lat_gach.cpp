#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
string s;
int dp[N][51];
ll n, k, G1, G2, G3;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> G1 >> G2 >> G3 >> s, s = ' ' + s;
  int total = 0;
  for (int i = 1; i <= n; ++i)
    if (s[i] == '.') total++;
  memset(dp, -0x3f, sizeof(dp)); ll inf = dp[0][0];
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) for (int j = 0; j <= 50; ++j) {
    dp[i][j] = dp[i - 1][j];
    if (i >= 2 && s[i] == '.' && s[i-1] == '.') dp[i][j] = max(dp[i][j], dp[i-2][j] + 1);
    if (i >= 3 && s[i] == '.' && s[i-1] == '#' && s[i-2] == '.')
      dp[i][j] = max(dp[i][j], dp[i-3][j-1]);
  }
  ll res = 0;
  for (int j = 0; j <= 50; ++j) if (dp[n][j] >= 0) {
    ll g1 = G1, g2 = G2, g3 = G3;
    ll cnt3 = j, cnt2 = dp[n][j], cnt1 = min(k, total - cnt3*2 - cnt2*2);
    if (cnt1 < 0) continue;
    if (g2 > g3) swap(g2, g3), swap(cnt2, cnt3);
    if (g1 * 2 > g2) {
      int x = min(cnt2, (k - cnt1) / 2);
      cnt1 += x * 2, cnt2 -= x;
    }
    if (g1 > g2 && cnt2 > 0 && cnt1 < k)
      cnt1++, cnt2--;
    swap(g2, g3), swap(cnt2, cnt3);
    if (g1 * 2 > g2) {
      int x = min(cnt2, (k - cnt1) / 2);
      cnt1 += x * 2, cnt2 -= x;
    }
    if (g1 > g2 && cnt2 > 0 && cnt1 < k)
      cnt1++, cnt2--;
    
    
    res = max(res, cnt1 * g1 + cnt2 * g2 + cnt3 * g3);
  }
  cout << res;
	return 0;
}

