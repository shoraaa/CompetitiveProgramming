#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 5;
vector<int> rig[N];
int c[N], d[N];
ll bit[N];
void update(int i, long long v) {
  for (; i > 0; i -= i & -i)
    bit[i] = max(bit[i], v);
}
ll get(int i) {
  ll res = 0;
  for (; i < N; i += i & -i)
    res = max(res, bit[i]);
  return res;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n; cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int i = 1; i <= n; i++)
    cin >> d[i];
  for (int i = n; i > 0; i--) {
    if (c[i] == 1) continue;
    if (i >= c[i])
      rig[i - c[i] + 1].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j : rig[i])
      update(j - 1, get(j) + d[j]);
    if (c[i] == 1)
      cout << d[i] + get(i) << ' ';
    else {
      cout << get(i) << ' ';
      if (i + c[i] - 1 <= n)
        update(i + c[i] - 1,
        get(i + c[i] - 1) + d[i]);
    }
  }
}