#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e7 + 3;
int b[N];
int n, k, F, M; ll A, B;

int dq[N]; ll dp[N];
int fi = 0, la = -1;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> F >> A >> B >> M;
  b[1] = F;
  for (int i = 2; i <= n; ++i)
    b[i] = (b[i - 1] * A + B) % M;
  dq[++la] = 0;
  for (int i = 1; i <= k; ++i) {
    dp[i] = dp[dq[fi]] + b[i];
    while (fi <= la && dp[dq[la]] >= dp[i]) la--;
    dq[++la] = i;
  }
  for (int i = k + 1; i <= n + 1; ++i) {
    if (fi <= la && dq[fi] < i - k) fi++;
    dp[i] = dp[dq[fi]] + b[i]; 
    while (fi <= la && dp[dq[la]] >= dp[i]) la--;
    dq[++la] = i;
  }
  cout << dp[n + 1];
	return 0;
}

