#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<int> pos[N];
int a[N], lin[N], siz[N];
int n;
int find(int i) {
  if (i == lin[i]) return i;
  return lin[i] = find(lin[i]);
}
ll res = 0; int cc;
void unite(int u, int v, int w) {
  u = find(u), v = find(v);
  if (u == v) return;
  if (siz[u] < siz[v]) swap(u, v);
  lin[v] = u, siz[u] += v; res += 123456 - w; cc--;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; cc = n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i]; lin[i] = i, siz[i] = 1; 
    for (int j = 1; j * j <= a[i]; ++j) if (a[i] % j == 0) {
      pos[j].emplace_back(i);
      if (j * j != a[i])
        pos[a[i] / j].emplace_back(i);
    }
  }
  for (int g = 1e5; g; --g) {
    vector<int> tplt;
    for (int i : pos[g])
      tplt.emplace_back(find(i));
    if (tplt.size() <= 1) continue;
    int head = tplt[0];
    for (int i = 1; i < tplt.size(); ++i)
      unite(head, tplt[i], g);
  }
  cout << res;
	return 0;
}

