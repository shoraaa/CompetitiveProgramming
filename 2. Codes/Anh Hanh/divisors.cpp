#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
vector<int> divi[N]; 
int dp[N];
int a, b;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("divisors.inp", "r"))
    freopen("divisors.inp", "r", stdin),
    freopen("divisors.out", "w", stdout);
  for (int i = 1; i < N; ++i) divi[i].reserve(32);
  for (int i = 2; i < N; ++i) for (int j = i * 2; j < N; j += i)
    divi[j].emplace_back(i);
  cin >> a >> b;
  memset(dp, 0x3f, sizeof(dp));
  dp[a] = 0;
  for (int x = a; x < b; ++x) if (dp[x] < 1e9) 
    for (int d : divi[x]) {
      if (x + d > N) break;
      dp[x + d] = min(dp[x + d], dp[x] + 1);
  }
  cout << (dp[b] > 1e9 ? -1 : dp[b]);
	return 0;
}

