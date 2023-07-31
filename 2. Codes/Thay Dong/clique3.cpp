#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e6 + 5;
int a[N], cnt[N], f[N];
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)  
    cin >> a[i];
  sort(a, a + n);
  ll res = 0;
  for (int i = n-1; ~i; --i) {
    for (int b = a[i] * 2; b <= a[n-1]; b += a[i])
      f[a[i]] += cnt[b], res += f[b];
    cnt[a[i]]++;
  }
  cout << res;
	return 0;
}

