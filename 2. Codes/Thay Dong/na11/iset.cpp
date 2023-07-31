#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
ll a[N], b[N], t[N], f[N][2];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> f[i][1];
  for (int i = 1; i <= n-1; ++i)
    cin >> b[i] >> t[i];
  for (int v = n-1; v; --v) {
    int u = b[v];
    if (t[v] == 0) {
      f[u][1] = f[v][0] + f[u][1];
      f[u][0] = max(f[v][0], f[v][1]) + f[u][0];
    } else if (t[v] == 1) {
      //f[u][1] = max(f[u][1] + max(f[v][0], f[v][1]), f[u][0] + f[v][1]);
      f[u][1] = max(f[v][1] + max(f[u][0], f[u][1]), f[v][0] + f[u][1]);
      f[u][0] = f[v][0] + f[u][0];
    } else {
      f[u][1] = max(f[v][1] + f[u][0], f[u][1] + f[v][0]);
      f[u][0] = f[v][0] + f[u][0];
    }
  }
  cout << max(f[0][0], f[0][1]);
	return 0;
}

