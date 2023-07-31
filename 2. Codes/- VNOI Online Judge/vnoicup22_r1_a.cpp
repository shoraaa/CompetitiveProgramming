#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
int a[N], b[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	if (a[n-1] != b[0]) cout << string(n, 'a') + string(n, 'b');
	else if (a[0] != b[n-1]) cout << string(n, 'b') + string(n, 'a');
	else cout << "a" + string(n, 'b') + string(n-1, 'a');
	return 0;
}

