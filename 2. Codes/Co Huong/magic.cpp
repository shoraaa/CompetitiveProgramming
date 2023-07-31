#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5, K = 31, inf = 1e9;
inline int bit(int msk, int i) {
  return msk >> i & 1;
}
struct Trie {
  static const int C = 5e6;
  int nxt[C][2], cnt[K][2], tot[K], min_idx[C], max_idx[C];
  set<int> s[C]; int id;
  Trie(): id(1) {
    tot[K-1] = cnt[K-1][0] = cnt[K-1][1] = 1;
    fill(begin(min_idx), end(min_idx), inf);
  }
  int cont1(int u) {
    if (!nxt[u][1] || min_idx[nxt[u][1]] == inf) return 1;
    if (!nxt[u][0] || max_idx[nxt[u][0]] == 0) return 1;
    return max_idx[nxt[u][0]] < min_idx[nxt[u][1]];
  }
  int cont2(int u) {
    if (!nxt[u][0] || min_idx[nxt[u][0]] == 0) return 1;
    if (!nxt[u][1] || max_idx[nxt[u][1]] == inf) return 1;
    return max_idx[nxt[u][1]] < min_idx[nxt[u][0]];
  }
  void add(int x, int idx, int i = K-1, int u = 0) {
    if (i == -1) {
      s[u].insert(idx);
      min_idx[u] = *s[u].begin();
      max_idx[u] = *s[u].rbegin();
      return;
    }
    int b = bit(x, i);
    if (!nxt[u][b]) {
      nxt[u][b] = id++;
      if (i != 0) {
        tot[i-1]++, cnt[i-1][0]++, cnt[i-1][1]++;
      }
    }
    cnt[i][0] -= cont1(u), cnt[i][1] -= cont2(u);
    add(x, idx, i-1, nxt[u][b]);
    cnt[i][0] += cont1(u), cnt[i][1] += cont2(u);
    min_idx[u] = min(min_idx[u], idx);
    max_idx[u] = max(max_idx[u], idx);
  }
  void erase(int x, int idx, int i = K-1, int u = 0) {
    if (i == -1) {
      s[u].erase(idx);
      min_idx[u] = s[u].empty() ? inf : *s[u].begin();
      max_idx[u] = s[u].empty() ? 0 : *s[u].rbegin();
      return;
    }
    int b = bit(x, i);
    cnt[i][0] -= cont1(u), cnt[i][1] -= cont2(u);
    erase(x, idx, i-1, nxt[u][b]);
    cnt[i][0] += cont1(u), cnt[i][1] += cont2(u);
    min_idx[u] = inf;
    if (nxt[u][0]) min_idx[u] = min(min_idx[u], min_idx[nxt[u][0]]);
    if (nxt[u][1]) min_idx[u] = min(min_idx[u], min_idx[nxt[u][1]]);
    
    max_idx[u] = 0;
    if (nxt[u][0]) max_idx[u] = max(max_idx[u], max_idx[nxt[u][0]]);
    if (nxt[u][1]) max_idx[u] = max(max_idx[u], max_idx[nxt[u][1]]);
  }
  
  int get() {
    int res = 0;
    for (int i = K-1; ~i; --i) {
      if (cnt[i][0] == tot[i]) continue;
      if (cnt[i][1] == tot[i]) res |= 1 << i;
      else return -1;
    }
    return res;
  }
} trie;
int a[N];
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("magic.in", "r"))
	  freopen("magic.in", "r", stdin),
	  freopen("magic.out", "w", stdout);
  cin >> n; 
  for (int i = 1; i <= n; ++i)
    cin >> a[i], trie.add(a[i], i);
  cout << trie.get() << '\n';
  cin >> q;
  for (int i = 0, p, v; i < q; ++i) {
    cin >> p >> v;
    trie.erase(a[p], p);
    a[p] = v;
    trie.add(a[p], p);
    cout << trie.get() << '\n';    
  }
	return 0;
}

