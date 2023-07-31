#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const ll inf = 1e16;
int a[N], n, L, R;  
ll pre[N], suf[N], C;
#define fi first
#define se second

ll dis(int l, int r) {
  if (l > r) swap(l, r);
  return min(r-l, n-(r-l)) * C;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("SWGAME.inp", "r"))
    freopen("SWGAME.inp", "r", stdin),
    freopen("SWGAME.out", "w", stdout);
  cin >> n >> L >> R; C = min(L, R);
  for (int i = 0; i < n; ++i)
    cin >> a[i], a[i] &= 1;
  vector<int> b; ll res = 0; b.emplace_back(0);
  for (int i = 0; i < n; ++i) if (a[i]) b.emplace_back(i);
  int m = b.size() - 1; 
  ll ans = inf;
  if (m % 2 == 0) {
    ll cur = 0;
    pre[1] = dis(b[1], b[m]);
    for (int i = 2; i <= m; ++i) 
      pre[i] = pre[i-2] + dis(b[i], b[i-1]);
    ans = min(pre[m], pre[m-1]);
    
  } else {
    
    pre[1] = dis(b[1], b[m]);
    for (int i = 2; i <= m; ++i)
      pre[i] = pre[i-2] + dis(b[i], b[i-1]);
    for (int i = m-1; i; --i)
      suf[i] = suf[i+2] + dis(b[i], b[i+1]);
    for (int i = 1; i <= m; ++i)
      ans = min(ans, pre[i-1] + suf[i+1]);
    
  }
  cout <<ans;
	return 0;
}

