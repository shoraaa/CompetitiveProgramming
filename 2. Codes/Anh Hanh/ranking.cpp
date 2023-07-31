#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "ranking";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3000 + 5;
array<int, 3> a[N];
int n;
ostream& operator << (ostream& os, array<int, 3> ar) {
	return os << ar[0] << ' ' << ar[1] << ' ' << ar[2] << '\n';
}
array<int, 3> normalize(array<int, 3> u) {
	array<int, 3> res = u;
	sort(u.rbegin(), u.rend());
	if (u[0] == u[1]) u[0]++, u[1] = 0;
	if (u[0] == u[2]) u[0]++, u[2] = 0;
	if (u[1] == u[2]) u[1]++, u[2] = 0;
}
int smaller(array<int, 3> u, array<int, 3> v) {
	sort(u.rbegin(), u.rend()); 
	sort(v.rbegin(), v.rend());
	return u < v;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
	cin >> n;
	for (int i = 0, x; i < n; ++i)
		cin >> x, a[i][0] = x;
	for (int i = 0, x; i < n; ++i)
		cin >> x, a[i][1] = x;
	for (int i = 0; i < n; ++i) {
		vector<array<int, 3>> b;
		for (int j = 0; j < n; ++j) if (j != i) 
			b.emplace_back(a[j]);
		sort(b.begin(), b.end());
		
		array<int, 3> cur = a[i]; 
		// tot nhat
		cur[2] = 1;
		cur = normalize(cur);
		int res = 0;
		// duyet tu kem nhat den tot nhat 
		for (int j = n-2, c = 2; ~j; --j) {
			do {
				b[j][2] = c, c++;
			} while (smaller(normalize(b[j]), cur) && c <= n);
			res += smaller(normalize(b[j]), cur);
		}
		cout << res + 1 << ' ';
		
		cur = a[i];
		cur[2] = n;
		cur = normalize(cur);
		res = 0;
		// duyet tu tot nhat den tot kem 
		for (int j = 0, c = n-1; j < n-1; ++j) {
			do {
				b[j][2] = c, c++;
			} while (!smaller(normalize(b[j]), cur) && c <= n);
			res += smaller(normalize(b[j]), cur);
		}
		cout << res + 1 << '\n';

		
	}
	return 0;
}

