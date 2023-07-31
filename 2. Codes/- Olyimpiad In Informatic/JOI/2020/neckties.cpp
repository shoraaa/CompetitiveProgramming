#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5;
int a[N], pre[N], C[N];
pair<int, int> b[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n + 1; ++i)
		cin >> b[i].first, b[i].second = i;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 2);
	for (int i = 1; i <= n; ++i)
		pre[i] = max(pre[i-1], b[i].first - a[i]);
	C[b[n+1].second] = pre[n];
	int cur_max = 0;
	for (int i = n; i; --i) {
		// thay ai bang ai+1
		cur_max = max(cur_max, b[i+1].first - a[i]);
		C[b[i].second] = max(pre[i-1], cur_max);
	}
	for (int i = 1; i <= n+1; ++i)
		cout << C[i] << ' ';		
	return 0;
}

