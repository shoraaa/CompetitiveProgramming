#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll pw[30], val[30];

int check(int n) {
  if (n >= 10 && n <= 18) return 1;
  for (int i = 2; i < 10; ++i)
    if (val[i] <= n && n <= val[i] * 2) return 1;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("mulgame.inp", "r")) 
    freopen("mulgame.inp", "r", stdin),
    freopen("mulgame.out", "w", stdout);
  pw[0] = 1;
  for (int i = 1; i < 10; ++i)
    pw[i] = pw[i - 1] * 9,
    val[i] = pw[i] * (1LL << (i - 1)) + 1;
  int T; cin >> T;
  while (T--) {
    int n; cin >> n; 
    cout << (check(n) ? "La deuxieme joueuse gagne.\n" : "La premiere joueuse gagne.\n");
  }
	return 0;
}

