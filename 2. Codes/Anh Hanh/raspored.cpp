#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5;
int t[N], d[N], c[N * 2], bit[N * 2];
int J[N], X[N], Y[N];
int n, m, q;
void update(int i, int x) {
  for (; i; i -= i & -i)
    bit[i] += x;
}
ll get(int i) {
  ll res = 0;
  for (; i <= m; i += i & -i)
    res += bit[i];
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int subtask; cin >> subtask;
  cin >> n >> q; ll res = 0;
  for (int i = 0; i < n; ++i)
    cin >> t[i] >> d[i], c[i] = d[i], res += t[i];
  sort(c, c + n);
  ll cur = 0;
  for (int i = 0; i < n; ++i)
    cur += c[i], res -= cur;
  cout << res << ' ';
  for (int i = 0; i < q; ++i)
    cin >> J[i] >> X[i] >> Y[i],
    c[n + i] = Y[i];
  sort(c, c + n + q);
  m = unique(c, c + n + q) - c;
  for (int i = 0; i < n; ++i) {
    d[i] = lower_bound(c, c + m, d[i]) - c + 1;
    update(d[i], 1);
  }
  for (int i = 0, j, x, y; i < q; ++i) {
    j = J[i] - 1, x = X[i], y = Y[i];
    res -= t[j]; cerr << "- " << t[j] << ' ';
    res += get(d[j]) * c[d[j] - 1];
    cerr << "- " << get(d[j]) * c[d[j] - 1] << ' ';
    update(d[j], -1);
    t[j] = x, d[j] = lower_bound(c, c + m, y) - c + 1;
    update(d[j], +1);
    cerr << "+ " << get(d[j]) * c[d[j] - 1] << ' ';
    res -= get(d[j]) * c[d[j] - 1];
    res += t[j]; cerr << "+ " << t[j] << '\n';
    cerr << get(d[j]) << ' ' << c[d[j] - 1] << '\n';
    cout << res << ' ';
  }
	return 0;
}

