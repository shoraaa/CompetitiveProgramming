#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e6 + 5;
int a[N];
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  ll res = 0;
  deque<int> q;
  for (int i = 0; i < k; ++i) {
    while (!q.empty() && a[i] <= a[q.back()]) q.pop_back();
    q.emplace_back(i); res += a[q.front()];
  }
  for (int i = k; i < n; ++i) {
    if (!q.empty() && q.front() <= i - k) q.pop_front();
    while (!q.empty() && a[i] <= a[q.back()]) q.pop_back();
    q.emplace_back(i); res += a[q.front()];
  }
  cout << res;
	return 0;
}

