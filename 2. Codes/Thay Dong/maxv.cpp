#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
string a[N];
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("maxv.INP", "r"))
    freopen("maxv.INP", "r", stdin),
    freopen("maxv.OUT", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  sort(a, a + n, [](string& u, string& v) {
    return u + v > v + u;
  });
  for (int i = 0; i < n; ++i)
    cout << a[i];
	return 0;
}

