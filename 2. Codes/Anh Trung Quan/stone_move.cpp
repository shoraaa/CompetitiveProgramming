#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, inf = 1e9;
int a[N], b[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  ll res = 0;
  for (int i = 0, x, y; i < n * 2; ++i) {
    cin >> x >> y;
    if (x <= 1) res += 1 - x, x = 1;
    else if (x >= n) res += x - n, x = n;
    
    if (y <= 1) res += 1 - y, a[x]++;
    else if (y >= 2) res += y - 2, b[x]++;
  }

  for (int i = 1; i <= n; ++i) {
    while (a[i] > 1 && b[i] <= 0) res++, a[i]--, b[i]++;
    while (b[i] > 1 && a[i] <= 0) res++, b[i]--, a[i]++;
    res += abs(a[i] - 1), a[i + 1] += a[i] - 1;
    res += abs(b[i] - 1), b[i + 1] += b[i] - 1; 
  }
  
  
  cout << res;
  
	return 0;
}

