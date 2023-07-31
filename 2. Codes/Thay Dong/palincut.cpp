#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e5 + 5;
string s;
int n, T, k;
int nxt[N][14], dp[1 << 14], l[14];
ull pw[N], pre[N], suf[N], b = 31;
ull pre_hash(int l, int r) {
  if (l == 0) return pre[r];
  return pre[r] - pre[l-1] * pw[r-l+1];
}
ull suf_hash(int l, int r) {
  if (r == n-1) return suf[l];
  return suf[l] - suf[r+1] * pw[r-l+1];
}
int palin(int l, int r) {
  return pre_hash(l, (l+r)/2) == suf_hash((l+r+1)/2, r);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s; n = s.size();
  pw[0] = 1, pre[0] = s[0]-'a'+1, suf[n-1] = s[n-1]-'a'+1;
  for (int i = 1; i < n; ++i)
    pw[i] = pw[i-1] * b,
    pre[i] = pre[i-1]*b + s[i]-'a'+1;
  for (int i = n-2; i >= 0; --i)
    suf[i] = suf[i+1]*b + s[i]-'a'+1;
  cin >> T;
  while (T--) {
    cin >> k;
    for (int i = 0; i < k; ++i) 
      cin >> l[i];
    for (int j = 0; j < k; ++j) nxt[n][j] = -1;
    for (int i = n-1; ~i; --i) for (int j = 0; j < k; ++j) {
      nxt[i][j] = nxt[i+1][j];
      if (palin(i, i + l[j] - 1)) nxt[i][j] = i + l[j] - 1;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = -1;
    for (int msk = 0; msk < 1 << k; ++msk) if (dp[msk] < n)
      for (int i = 0; i < k; ++i) if (!(msk >> i & 1) && ~nxt[dp[msk] + 1][i])
        dp[msk ^ (1 << i)] = min(dp[msk ^ (1 << i)], nxt[dp[msk] + 1][i]);
    cout << (dp[(1 << k) - 1] < n ? "YES\n" : "NO\n");
  }
	return 0;
}

