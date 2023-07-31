#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
int n, m;
vector<pair<int, int>> pos;
void insert(int lef, int rig, int type) {
  if (lef > rig) return;
  pos.emplace_back(lef, -type);
  pos.emplace_back(rig + 1, +type);
}
int cnt[N], tot = 0;
void insert(int t) {
  if (!cnt[t]) tot++; cnt[t]++;
}
void erase(int t) {
  cnt[t]--; if (!cnt[t]) tot--;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> m >> n;
  for (int i = 1, k; i <= n; ++i) {
    cin >> k; vector<int> a(k);
    int lef = 1, rig = m;
    for (int& x : a) 
      cin >> x, rig -= x;
    insert(lef, rig, i);
    for (int x : a) 
      lef += x, rig += x,
      insert(lef, rig, i);
  }
  sort(pos.begin(), pos.end());
  int k = pos.size(), res = 0; pos.emplace_back(m + 1, -1);
  for (int i = 0; i < k; ++i) {
    int p = pos[i].first, t = pos[i].second;
    if (t < 0) insert(-t);
    else erase(t);
    if (tot == n)
      res += pos[i+1].first - p;
  }
  cout << m - res;
	return 0;
}

