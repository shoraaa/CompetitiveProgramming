#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105;
int last[N], cur[N], wrong[N], cnt[N];
int k, n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("duaxe.inp", "r")) 
    freopen("duaxe.inp", "r", stdin),
    freopen("duaxe.out", "w", stdout);
  cin >> k >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    if (wrong[x]) continue;
    if (last[x] + 1 == y) {
      if (y == k) y = 0; 
      last[x] = y, cur[x] = i, cnt[x]++;
    } else { 
      wrong[x] = 1;
    }
  }
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  sort(a.begin(), a.end(), [&](int i, int j) {
    if (cnt[i] != cnt[j]) return cnt[i] > cnt[j];
    return cur[i] < cur[j];
  });
  for (int i : a) cout << i << ' ';
	return 0;
}

