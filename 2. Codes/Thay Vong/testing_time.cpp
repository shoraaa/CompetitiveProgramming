#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N];
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	freopen("test_input.txt", "r", stdin);
	cin >> n >> q;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < 30; ++i) {
		sort(a, a + n);
	}
	return 0;
}

