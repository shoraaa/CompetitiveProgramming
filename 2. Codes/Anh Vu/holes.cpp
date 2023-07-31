#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, K = 314;
int nxt[N];
pair<int, int> cnxt[N];
int n, m;
pair<int, int> get(int i) {
  if (cnxt[i].first == i)
    return {i, 1};
  auto p = get(cnxt[i].first); 
  p.second += cnxt[i].second;
  return p;
}
void update(int pos, int pnxt) {
  nxt[pos] = pnxt;
  int l = pos / K * K, r = min(l + K - 1, n-1);
  for (int i = r; i >= l; --i)
    if (nxt[i] >= n)
      cnxt[i] = {i, 0};
    else if (i / K != nxt[i] / K)
      cnxt[i] = {nxt[i], 1};
    else
      cnxt[i] = cnxt[nxt[i]], cnxt[i].second++;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, l; i < n; ++i) 
    cin >> l, nxt[i] = i + l;
  for (int i = n-1; ~i; --i)
    if (nxt[i] >= n)
      cnxt[i] = {i, 0};
    else if (i / K != nxt[i] / K)
      cnxt[i] = {nxt[i], 1};
    else
      cnxt[i] = cnxt[nxt[i]], cnxt[i].second++;
    
    
  for (int i = 0, t, a, b; i < m; ++i) {
    cin >> t >> a, a--;
    if (t == 0)
      cin >> b, 
      update(a, a + b);
    else {
      auto p = get(a);
      cout << p.first + 1 << ' ' << p.second << '\n';
    }
  }
	return 0;
}

