#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  set<pair<int, int>> s;
  for (int i = 0, deg; i < n; ++i) 
    cin >> deg, s.insert({deg, i + 1});
  if (n == 1)
    return 0;
  while (!s.empty()) {
    auto mn = s.begin(); assert(mn->first == 1);
    auto pmn = *mn; s.erase(mn); pmn.first--;
    auto mx = s.end(); mx--;
    auto pmx = *mx; s.erase(mx); pmx.first--;
    cout << pmn.second << ' ' << pmx.second << '\n';
    if (pmn.first) s.insert(pmn);
    if (pmx.first) s.insert(pmx);
  }
	return 0;
}

