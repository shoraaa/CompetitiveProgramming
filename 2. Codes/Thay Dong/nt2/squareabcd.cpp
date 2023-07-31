#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 405;

int x[N], y[N], l[N], Left[N], Right[N], down[N], top[N];
int n;

vector<int> cut(int i, int j) {
  int len = l[i];
  int lef = max(Left[i], Left[j]), rig = min(Right[i], Right[j]);
  int dow = max(down[i], down[j]), to = min(top[i], top[j]);
  
  if (lef >= rig || dow >= to) 
    lef = rig = dow = to = 0;
  else if (lef == Left[i] && rig == Right[i] && dow == down[i] && to == top[i]) 
    len = lef = rig = dow = to = 0;  
  else {
    lef -= x[i], rig -= x[i], dow -= y[i], to -= y[i];
    if (rig == l[i] && dow == 0 && to == l[i]) rig -= lef, lef = 0;
    if (to == l[i] && lef == 0 && rig == l[i]) to -= dow, dow = 0;
  }
  return {len, lef, rig, dow, to};
}

map<vector<int>, vector<pair<int, int>>> poly;
map<int, int> cnt;
map<pair<int, int>, int> cnt2;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i] >> l[i];
    // (x, y), (x + l, y), (x + l, y + l), (x, y + l)
    down[i] = y[i], top[i] = y[i] + l[i];
    Left[i] = x[i], Right[i] = x[i] + l[i];
  }
  
  ll res = 0;
  
  for (int a = 0; a < n; ++a) for (int b = 0; b < n; ++b) if (a != b)
    poly[cut(a, b)].emplace_back(min(a, b), max(a, b));

  for (auto& pi : poly) {
    vector<pair<int, int>> vec = pi.second;
    int tot = 0;
    
    for (auto& p : vec) {
      int a = p.first, b = p.second;
      res += tot - cnt[a] - cnt[b] + cnt2[{a, b}]; // so cap (c,d) ma a!=b!=c!=d
      cnt[a]++; cnt[b]++; cnt2[{a, b}]++; tot++;
    }
    
    for (auto& p : vec) {
      int a = p.first, b = p.second;
      cnt[a]--; cnt[b]--; cnt2[{a, b}]--;
    }
  }
    
  cout << res * 2;
  
  
	return 0;
}

