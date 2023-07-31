#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5;
int cnt[2][N];
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    cnt[0][0] = k;
    int pos = 0;
    for (int i = 0; i < n-1; ++i) {
      int cur = i & 1, nxt = cur ^ 1;
      memset(cnt[nxt], 0, (i + 2) * sizeof(int));
      for (int j = i; ~j; --j) {
        cnt[nxt][j] += (cnt[cur][j] + 1) / 2;
        cnt[nxt][j + 1] += cnt[cur][j] / 2;
        if (j == pos) pos += cnt[cur][j] % 2 == 0;
      }
    }
    cout << pos << '\n';
  }
	return 0;
}

