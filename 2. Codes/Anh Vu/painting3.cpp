#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
struct Tp {
  int a, b, c;
  Tp() = default;
  Tp(int a, int b, int c): a(a), b(b), c(c) {}
  operator < (const Tp& t) const {
    return a-b > t.a-t.b;
  }
} a[N];
ll pre[N], suf[N];
int n, x, y, z;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> x >> y >> z, n = x + y + z;
  for (int i = 0; i < n; ++i)
    cin >> a[i].a;
  for (int i = 0; i < n; ++i)
    cin >> a[i].b;
  for (int i = 0; i < n; ++i)
    cin >> a[i].c;
  sort(a, a + n);
  ll cur = 0; priority_queue<int> q;
  for (int i = 0; i < x; ++i)
    cur += a[i].a, q.emplace(-a[i].a + a[i].c);
  pre[x-1] = cur;
  for (int i = x; i < n-y; ++i) {
    cur += a[i].a, q.emplace(-a[i].a + a[i].c);
    cur += q.top(); q.pop();
    pre[i] = cur;
  }
  cur = 0; q = priority_queue<int>();
  for (int i = n-1; i >= n-y; --i) 
    cur += a[i].b, q.emplace(-a[i].b + a[i].c);
  suf[n-y] = cur;
  for (int i = n-y-1; i >= x; --i) {
    cur += a[i].b, q.emplace(-a[i].b + a[i].c);
    cur += q.top(); q.pop();
    suf[i] = cur;
  }
  ll res = 0;
  for (int i = x-1; i < n-y; ++i)
    res = max(res, pre[i] + suf[i+1]);
  cout << res;
	return 0;
}

