#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N];
int n, q;
int main() {
	std::ios::sync_with_stdio(false);
	freopen("test_input.txt", "r", stdin);
	cin >> n >> q;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < 20; ++i) {
		stable_sort(a, a + n);
	}
	return 0;
}

