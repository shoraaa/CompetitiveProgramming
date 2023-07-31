#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int a[N];
pair<int, int> bit[N], dp[N];
int n;
pair<int, int> get(int i) {
	pair<int, int> res = {0, 0};
	for (; i; i -= i & -i)
		res = max(res, bit[i]);
	return res;
}
void update(int i, pair<int, int> v) {
	for (; i <= N; i += i & -i)
		bit[i] = max(bit[i], v);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	
	pair<int, int> res = {0, 0};
	for (int i = 1; i <= n; ++i)
		dp[i] = get(a[i] - 1), 
		dp[i].first++,
		update(a[i], {dp[i].first, i}),
		res = max(res, {dp[i].first, i});
		
	cout << res.first << '\n';
	stack<int> st;
	for (int i = res.second; i; i = dp[i].second)
		st.emplace(i);
	while (!st.empty())
		cout << st.top() << ' ', st.pop(); 
	return 0;
}

