#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
string s;
int f[N]; 
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s; 
  for (int i = 1; i <= n; ++i)
    f[i] = f[i - 1] + (s[i - 1] == '1');
  for (int i = 1; i <= n; ++i) {
    int cur = 0;
    for (int j = 1; j + i - 1 <= n; ++j) 
      cur = max(cur, f[j + i - 1] - f[j - 1]);
    int k = min(n, int(1.05 * i));
    for (int j = i; j <= k; ++j) cout << cur << ' ';
    i = k;
  }
	return 0;
}

