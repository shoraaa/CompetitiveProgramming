#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int a[N], lin[N], siz[N];
pair<int, int> b[N], c[N];
ll res[N];
int n, m;
ll cur = 0;
int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return;
  if (siz[u] < siz[v]) swap(u, v);
  lin[v] = u, siz[u] += siz[v];
}
ll f(ll len) {
  return len * (len + 1) / 2;
}
void insert(int i) {
  if (i && siz[find(i-1)]) cur -= f(siz[find(i-1)]), unite(i, i-1);
  if (i < n-1 && siz[find(i+1)]) cur -= f(siz[find(i+1)]), unite(i, i+1);
  siz[find(i)]++, cur += f(siz[find(i)]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = {a[i], i};
  for (int i = 0; i < m; ++i)
    cin >> b[i].first, b[i].second = i;
  sort(c, c + n);
  sort(b, b + m);
  for (int i = 0; i < n; ++i)
    lin[i] = i;
  for (int i = 0, j = 0; i < m; ++i) {
    while (j < n && c[j].first <= b[i].first) insert(c[j].second), j++;
    res[b[i].second] = cur;
  }
  for (int i = 0; i < m; ++i)
    cout << res[i] << '\n';
	return 0;
}

