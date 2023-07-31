#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<int> seq[N];
vector<array<pair<int, int>, 20>> spt[N];
map<int, int> cnt;
int m = 0;
int n;
pair<int, int> get_min(int l, int r) {
  int k = __lg(r-l+1);
  return min(spt[l][k], spt[r-(1<<k)+1][k]);
}
void solve(int l, int r, int delta = 0) {
  if (l > r) return;
  auto mn = get_min(l, r); mn.first -= delta;
  if (mn.first) b[m++] = {r - l + 1, mn.first};
  solve(l, mn.second - 1, delta + mn.first);
  solve(mn.second + 1, r, delta + mn.first);
}
void decompose(vector<int>& a) {
  n = a.size(); 
  seq[m] = a;
  spt[m].resize(n);
  for (int i = 0; i < n; ++i)
    spt[m][i][0] = {a[i], -i};
  for (int k = 1; k < 20; ++k)
    for (int i = 0; i + (1 << k) - 1 < n; ++i)
      spt[m][i][k] = min(spt[m][i][k-1], spt[m][i+(1<<(k-1))][k-1]);
  m++;
}
int calc(int k) {
  for (int id = 0; id < m; ++id) {
    for (int i = 0; ;) {
      if (i + k - 1 >= n) break;
      auto mn = min
      
    }
  }
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int n, c, L, R;
  cin >> n >> c >> L >> R;
  for (int i = 0, x; i < n; ++i)  
    cin >> x, cnt[x]++;
  for (auto& p : cnt) if (p.second) {
    vector<int> cur;
    for (int j = p.first; cnt.count(j) && cnt[j]; j += c) 
      cur.emplace_back(cnt[j]), cnt[j] = 0;
    decompose(cur);
  }
  for (int i = L; i <= R; ++i)
    cout << calc(i) << ' ';
	return 0;
}

