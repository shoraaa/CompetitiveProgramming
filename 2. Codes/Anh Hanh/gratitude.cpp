#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
  const string FILE_NAME = "gratitude";
  freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
  freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
map<string, int> idx;
int cnt[N], last[N];
string s, str[N];
vector<int> a;
int n, k, m = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n >> k;
  getline(cin, s);
  for (int i = 0, id; i < n * 3; ++i) {
    getline(cin, s);
    if (idx.count(s))
      id = idx[s];
    else
      id = m++,
      idx[s] = id,
      str[id] = s,
      a.emplace_back(id);
    cnt[id]++, last[id] = i;
  }
  sort(a.begin(), a.end(), [&](int u, int v) {
    if (cnt[u] == cnt[v])
      return last[u] > last[v];
    return cnt[u] > cnt[v];
  });
  for (int i = 0; i < min(k, (int)a.size()); ++i)
    cout << str[a[i]] << '\n';
	return 0;
}

