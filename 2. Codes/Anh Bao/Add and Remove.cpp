#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 20;

const ll inf = 1e18;

int n;
int a[N];
ll call(int l, int r, int p1, int p2) {
  if (l > r) return 0;
  ll res = inf;
  for (int i = l; i <= r; ++i)
    res = min(res, call(l, i-1, p1, p1 + p2) + call(i+1, r, p1 + p2, p2) + a[i] * ll(p1 + p2));
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  cout << call(1, n-2, 1, 1) + a[0] + a[n-1];
	return 0;
}

