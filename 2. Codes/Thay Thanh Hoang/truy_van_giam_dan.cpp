#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int a[2][N];
int n, q;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  for (int i = 0; i < n; ++i)
    cin >> a[0][i];
  sort(a[0], a[0] + n);
  for (int i = 0, x, y; i < q; ++i) {
    cin >> x >> y;
    int cur = i&1, nxt = cur^1;
    int j1 = 0, j2 = n-y, j = 0;
    while (j1 < n-y && j2 < n) {
      if (a[cur][j1] <= a[cur][j2] - x) a[nxt][j++] = a[cur][j1], j1++;
      else a[nxt][j++] = a[cur][j2] - x, j2++;
    } 
    while (j1 < n-y) a[nxt][j++] = a[cur][j1], j1++;
    while (j2 < n) a[nxt][j++] = a[cur][j2] - x, j2++;
  }
  for (int i = n-1; ~i; --i)
    cout << a[q&1][i] << ' ';
	return 0;
}

