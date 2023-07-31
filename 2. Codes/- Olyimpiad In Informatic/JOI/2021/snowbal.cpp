#include<bits/stdc++.h>
#define print(_v) for (auto& _e : _v) {cerr << _e << ' ';} cerr << '\n';
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5;
int a[N], b[N];
int n, q;
vector<pair<ll, ll>> c;
int pre_calc() {
	pair<ll, ll> ele = {0, 0};
	vector<int> pos, neg;
	if (b[0] >= 0) neg.emplace_back(0);
	for (int i = 1; i <= q; ) {
		int j = i; ll sum = 0;
		if (b[i] >= 0) {
			while (j <= q && b[j] >= 0) sum += b[j], j++;
			pos.emplace_back(sum);
		} else {
			while (j <= q && b[j] <= 0) sum += b[j], j++;
			neg.emplace_back(sum);
			if (i == q + 1) pos.emplace_back(0);
		}
		i = j;
	}
	print(pos);
	print(neg);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	// min(pre[i], D - min[i])
	// -> day tang roi giam
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= q; ++i)
		cin >> b[i];
	pre_calc();
	solve();
	for (int i = 1; i <= n; ++i)
		a[i] = -a[i];
	reverse(a + 1, a + n + 1);
	pre_calc();
	solve();
	for (int i = 1; i <= n; ++i)
		cout << res[i] + 1 << ' ';
	return 0;
}

