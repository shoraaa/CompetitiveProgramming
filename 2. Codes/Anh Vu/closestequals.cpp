#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5, K = 700;
struct Q {
  int l, r, i;
  Q(int l, int r, int i): l(l), r(r), i(i) {}
  bool operator < (const Q& q) const {
    if (l / K == q.l / K) return r < q.r;
    return l < q.l;
  }
};
vector<Q> que;
int a[N], lef[N], rig[N], res[N];
int n, q;
stack<int> st;
int lef_ans, rig_ans;
void incr(int i) {
  if (lef[a[i]] != -1)
    rig_ans = min(rig_ans, i - lef[a[i]]);
  lef[a[i]] = i;
  if (rig[a[i]] == -1)
    rig[a[i]] = i;
}
void decl(int i) {
  if (rig[a[i]] != -1)
    lef_ans = min(lef_ans, rig[a[i]] - i);
  st.push(rig[a[i]]);
  rig[a[i]] = i;
}
void rollback(int i) {
  rig[a[i]] = st.top();
  st.pop();
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q; vector<int> c(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = a[i];
  sort(c.begin(), c.end());
  c.erase(unique(c.begin(), c.end()), c.end());
  for (int i = 0; i < n; ++i)
    a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
  memset(res, 0x3f, sizeof(res));
  for (int id = 0, l, r; id < q; ++id) {
    cin >> l >> r, l--, r--;
    if (l / K == r / K) {
      for (int i = l; i <= r; ++i) 
        lef[a[i]] = -1;
      for (int i = l; i <= r; ++i) {
        if (lef[a[i]] != -1) 
          res[id] = min(res[id], i - lef[a[i]]);
        lef[a[i]] = i;
      } 
    } else que.emplace_back(l, r, id);
  }
  sort(que.begin(), que.end());
  for (int i = 0; i < que.size();) {
    int last = -1e9, j = i;
    while (j < q && que[i].l / K == que[j].l / K) 
      last = max(last, que[j].l), j++;
    j--;
    memset(lef, -1, sizeof(lef));
    memset(rig, -1, sizeof(rig));
    int l = last, r = last; incr(l);
    rig_ans = 1e9;
    for (int k = i; k <= j; ++k) {
      lef_ans = 1e9;
      while (r < que[k].r) incr(++r);
      while (l > que[k].l) decl(--l);
      res[que[k].i] = min(lef_ans, rig_ans);
      while (l < last) rollback(l++);
    }
    i = j + 1;
  }
  for (int i = 0; i < q; ++i)
    cout << (res[i] > n ? -1 : res[i]) << '\n';
	return 0;
}

