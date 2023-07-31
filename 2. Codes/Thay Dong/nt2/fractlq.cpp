#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 5e6 + 5;
const ll base = 31;

ull h[N], pw[N];

ull get(int l, int r) {
  return h[r] - h[l - 1] * pw[r - l + 1];
}

ll p, q, k;
string s, sc, t;
int vis[N], cnt[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> p >> q >> k >> t; p %= q;

  memset(vis, -1, sizeof(vis));
  for (int i = 0; p > 0; ++i) {
    if (~vis[p]) {
      // tu vis[p] den i-1 la phan bi trung
      int len = i - vis[p];
      while (len--) {
        sc += s.back(); s.pop_back();
      }
      reverse(sc.begin(), sc.end());
      break;
    }
    vis[p] = i;
    ll c = p * 10 / q;
    s += c + '0'; p = p * 10 - c * q;
  }
  if (sc.empty()) sc = '0';
  
  //cerr << s << '(' << sc << ")\n";
  
  int l = s.size(), r = l + sc.size() - 1;
  // [l, r]
  while (r + t.size() - 1 >= s.size()) s += sc;
  
  //cerr << s << '\n';
  
  int n = s.size();
  s = ' ' + s; l++, r++;
  
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    h[i] = h[i - 1] * base + s[i] - '0' + 1;
    pw[i] = pw[i - 1] * base;
  }
  
  int m = t.size();
  t = ' ' + t;
  
  ull val = 0;
  for (int i = 1; i <= m; ++i) {
    val = val * base + t[i] - '0' + 1;
  }
  
  for (int i = 1; i < l; ++i) {
    if (get(i, i + m - 1) == val) k--;
    if (k == 0) {
      cout << i; 
      return 0;
    }
  }
  
  int sum = 0;
  for (int i = l; i <= r; ++i) {
    cnt[i - l] = get(i, i + m - 1) == val;
    sum += cnt[i - l];
  }
  
  if (sum == 0) {
    cout << -1;
    return 0;
  }
  
  // sum * c < k <> c < k / sum
  int c = k % sum == 0 ? k / sum - 1 : k / sum;
  ll res = l - 1 + ll(sc.size()) * c;
  
  k -= c * sum;
  for (int i = 0; i < sc.size(); ++i) {
    k -= cnt[i]; res++;
    if (k == 0) {
      cout << res;
      return 0;
    }
  }
  
  
	return 0;
}

