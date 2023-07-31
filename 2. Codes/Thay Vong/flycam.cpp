#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "flycam";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
int a[N], f[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n;
  for (int i = 1; i <= n; ++i)  
    cin >> a[i];
  vector<pair<int, int>> f;
  for (int i = 1; i < n; ++i)
    f.emplace_back(min(a[i], a[i+1]), 1), 
    f.emplace_back(max(a[i], a[i+1]), -1);
  sort(f.begin(), f.end());
  pair<int, int> res = {0, 0};
  int cur = 0;
  for (int i = 0; i < f.size(); ) {
    int j = i;
    while (j < f.size() && f[j].first == f[i].first)
      cur += f[j].second, j++;
    res = max(res, {cur, i}), i = j;
  }
  cout << res.first;
	return 0;
}

