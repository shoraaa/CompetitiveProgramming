#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 6e5 + 5;
ll a[N], X;
int n, m = 0;

#define fi first
#define se second

pair<int, ll> bit1[N], bit2[N]; 
ll c[N];
void update(int i, ll v, int nv) {
  for (int j = i; j <= m; j += j & -j) bit1[j].fi += nv, bit1[j].se += v;
  for (int j = i; j; j -= j & -j) bit2[j].fi += nv, bit2[j].se += v;
}
pair<ll, ll> get_prefix(int i) {
  pair<ll, ll> res = {0, 0};
  for (; i; i -= i & -i) res.fi += bit1[i].fi, res.se += bit1[i].se;
  return res;
}
pair<ll, ll> get_suffix(int i) {
  pair<ll, ll> res = {0, 0};
  for (; i <= m; i += i & -i) res.fi += bit2[i].fi, res.se += bit2[i].se;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> X;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], a[n + i] = a[i];
  for (int i = 1; i <= n * 2; ++i) a[i] += a[i-1];
  for (int i = 0; i <= n * 2; ++i) c[m++] = a[i];
  sort(c, c + m); m = unique(c, c + m) - c;
  // dem sl va tong f[r]-f[l-1] <= X va c <= l <= r <= n+c
  // -> moi lan minh tien tien doan len, loai bo mot so cap su dung vi tri c cu (f[c-1])
  ll sum = 0; int cnt = 0;
  update(lower_bound(c, c + m, a[0]) - c + 1, a[0], 1);
  for (int i = 1; i <= n; ++i) {
    // dem so cap f[j] ma j < i va f[i]-X <= f[j]
    auto p = get_suffix(lower_bound(c, c + m, a[i] - X) - c + 1);
    cnt += p.fi; sum += a[i] * p.fi - p.se; 
    // cap nhat i
    update(lower_bound(c, c + m, a[i]) - c + 1, a[i], 1);
  }
  cout << sum << ' ' << cnt << '\n';
  for (int i = n + 1; i < n * 2; ++i) {
    // nhung cap su dung f[i - n - 1] -> dem so cap f[j] <= X-f[i-n-1] 
    update(lower_bound(c, c + m, a[i - n - 1]) - c + 1, -a[i - n - 1], -1);
    auto p = get_prefix(upper_bound(c, c + m, X + a[i - n - 1]) - c);
    cnt -= p.fi; sum -= p.se - p.fi * a[i - n - 1]; 
    p = get_suffix(lower_bound(c, c + m, a[i] - X) - c + 1);
    cnt += p.fi; sum += a[i] * p.fi - p.se; 

    update(lower_bound(c, c + m, a[i]) - c + 1, a[i], 1);
    cout << sum << ' ' << cnt << '\n';
  }
	return 0;
}

