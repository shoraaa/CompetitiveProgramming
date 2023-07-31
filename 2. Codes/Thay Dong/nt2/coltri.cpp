#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e6 + 5;
int lp[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  for (int i = 2; i * i < N; ++i)
    if (!lp[i]) for (int j = i * i; j < N; j += i) lp[j] = i;
  
  for (int i = 2; i < N; ++i) {
    if (lp[i]) lp[i] = lp[i - 1];
    else lp[i] = lp[i - 1] + 1; 
  }
  
  int T; cin >> T;
  while (T--) {
  cin >> n;
    
  ll res = 0;
  for (int i = 1; i <= n; ++i) {
    int x = lp[i + n] - lp[i];
    if (i == 1) x -= 1;
    int y = n - 1 - x;
    res += 1LL * x * y;
  }
  cout << 1LL * n * (n - 1) * (n - 2) / 6 - res / 2 << '\n';
  }
	return 0;
}

