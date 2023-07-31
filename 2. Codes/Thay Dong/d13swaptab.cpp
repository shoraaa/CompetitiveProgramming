#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
ll a[5];
#define bit(x, i) (x & (1LL << (i - 1)))
int n;
vector<int> last;
const int M = 1e9 + 7, L = 40;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M; 
}
int f[L*L*L*L*L];
bitset<L*L*L*L*L> v;
#define dp(id) f[id[0]*2560000 + id[1]*64000 + id[2]*1600 + id[3]*40 + id[4]]
#define vis(id) v[id[0]*2560000 + id[1]*64000 + id[2]*1600 + id[3]*40 + id[4]]
int call(vector<int>& id) {
  if (id == last) return 1;
  if (vis(id)) return dp(id);
  
  int res = 0; 
  for (int i = 0; i < n; ++i) 
    if (id[i] && bit(a[i], id[i]) == 0) 
      id[i]--, add(res, call(id)), id[i]++;
    
  for (int i = 0; i < n; ++i) {
    int nxt = (i + 1) % n;
    if (id[i] && id[nxt] && bit(a[i], id[i]) && bit(a[nxt], id[nxt]))
      id[i]--, id[nxt]--, add(res, call(id)), id[i]++, id[nxt]++;
  }
  return vis(id) = 1, dp(id) = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  vector<int> id(n); last = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    id[i] = 64 - __builtin_clzll(a[i]);
  }
  cout << call(id);
	return 0;
}

