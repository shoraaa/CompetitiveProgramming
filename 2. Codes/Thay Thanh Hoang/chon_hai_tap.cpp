#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e6 + 5;
int n, m;

int a[N], b[N], vis[N];
pair<int, int> idx[N];
#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; 
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  cin >> m;
  for (int i = 1; i <= m; ++i)
    cin >> b[i];
  
  int c = n; 
  idx[c] = {0, 0}, vis[c] = 1;
  for (int i = 0, j = 0;;) {
    if (c <= n) c += a[++i];
    else c -= b[++j];
    if (vis[c]) {
      cout << i - idx[c].fi << '\n';
      for (int j = idx[c].fi + 1; j <= i; ++j) 
        cout << j - 1 << ' ';
      cout << '\n' << j - idx[c].se << '\n'; 
      for (int i = idx[c].se + 1; i <= j; ++i) 
        cout << i - 1 << ' ';
      return 0;
    }
    vis[c] = 1, idx[c] = {i, j};
  }
	return 0;
}

