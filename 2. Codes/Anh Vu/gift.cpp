#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
void file() {
	const string FILE_NAME = "gift";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct I {
  int l, r;
  I(int l, int r): l(l), r(r) {}
  bool operator < (const I& itv) const {
    if (l == itv.l) return r < itv.r;
    return l < itv.l;
  }
};
vector<I> its, chk, mits;
int ctr[N], ctb[N];
int gtr(int l, int r) {
  if (l == 0) return ctr[r];
  return ctr[r] - ctr[l-1];
}
int gtb(int l, int r) {
  if (l == 0) return ctb[r];
  return ctb[r] - ctb[l-1];
}
int n, m;
char neg(char ch) {
  if (ch == 'R') return 'B';
  return 'R';
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n >> m;
  string s(n, '0');
  for (int i = 0, l, r, x; i < m; ++i) {
    cin >> l >> r >> x;
    if (x == 1) its.emplace_back(l, r);
    else chk.emplace_back(l, r);
  } 
  sort(its.begin(), its.end());
  for (int i = 0; i < its.size();) {
    int j = i, r = its[i].r;
    while (j < its.size() && its[j].l <= r)
      r = max(r, its[j].r), j++;
    mits.emplace_back(its[i].l, r);
    i = j;
  }
  char cur = 'R';
  for (int i = 0, j = 0; i < n; ++i) {
    if (j < mits.size() && i == mits[j].l) {
      for (; i <= mits[j].r; ++i) s[i] = cur;
      j++, i--;
    } else s[i] = cur;
    cur = neg(cur);
  } 
  ctr[0] = s[0] == 'R';
  ctb[0] = s[0] == 'B';
  for (int i = 1; i < n; ++i)
    ctr[i] = ctr[i-1] + (s[i] == 'R'),
    ctb[i] = ctb[i-1] + (s[i] == 'B');
  for (auto& it : chk) if (!gtr(it.l, it.r) || !gtb(it.l, it.r))
    return cout << 0, 0;
  cout << 1 << '\n' << s;
	return 0;
}

