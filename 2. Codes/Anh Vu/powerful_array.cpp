#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5, BLOCK = 450;
struct Q {
  int l, r, i; 
  Q(int l, int r, int i): l(l), r(r), i(i) {}
  bool operator < (const Q& q) const {
    if (l / BLOCK == q.l / BLOCK) return r < q.r;
    return l / BLOCK < q.l / BLOCK;
  }
};
vector<Q> que;
int a[N];
ll cnt[N], ans[N], res = 0;
int n, q;
void insert(int i) {
  int x = a[i];
  res += 2 * cnt[x] * x + x;
  cnt[x]++;
}
void erase(int i) {
  int x = a[i];
  cnt[x]--;
  res -= 2 * cnt[x] * x + x;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q; que.reserve(q);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0, l, r; i < q; ++i)
    cin >> l >> r, l--, r--,
    que.emplace_back(l, r, i);
  sort(que.begin(), que.end());
  int l = 0, r = 0; insert(0);
  for (auto& qr : que) {
    while (r < qr.r) insert(++r);
    while (r > qr.r) erase(r--);
    while (l < qr.l) erase(l++);
    while (l > qr.l) insert(--l);
    ans[qr.i] = res;
  }
  for (int i = 0; i < q; ++i)
    cout << ans[i] << ' ';
	return 0;
}

