#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int nxt[N][30];
int n, q;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i)
    cin >> nxt[i][0];
  for (int k = 1; k < 30; ++k)
    for (int i = 1; i <= n; ++i)
      nxt[i][k] = nxt[nxt[i][k-1]][k-1];
  for (int i = 0, u, k; i < q; ++i) {
    cin >> u >> k;
    for (int i = 0; i < 30; ++i)
      if (k >> i & 1) u = nxt[u][i];
    cout << u << '\n';
  }
	return 0;
}

