#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "topovi";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
	ll n;
	cin >> n;
	int k, p;
	cin >> k >> p;
	map<int, int> xor_row, xor_col;
	map<pair<int, int>, int> val;
	for (int i = 0, r, c, x; i < k; ++i)
		cin >> r >> c >> x, 
		xor_row[r] ^= x,
		xor_col[c] ^= x,
		val[{r, c}] = x;
	map<int, int> cnt_xor_row, cnt_xor_col;
	cnt_xor_row[0] = cnt_xor_col[0] = n;
	for (auto& p : xor_row) if (p.second) 
		cnt_xor_row[p.second]++,
		cnt_xor_row[0]--;
	for (auto& p : xor_col) if (p.second) 
		cnt_xor_col[p.second]++,
		cnt_xor_col[0]--;
		
	
	ll res = 0;
	for (auto& p : cnt_xor_row)
		res += 1LL * p.second * cnt_xor_col[p.first];
		
	auto change = [&](int r, int c, int x) {
		res -= cnt_xor_row[xor_col[c]];
		res -= cnt_xor_col[xor_row[r]];
		if (xor_col[c] == xor_row[r]) res++;
		
		cnt_xor_row[xor_row[r]]--;
		xor_row[r] ^= x;
		cnt_xor_row[xor_row[r]]++;
		
		cnt_xor_col[xor_col[c]]--;
		xor_col[c] ^= x;
		cnt_xor_col[xor_col[c]]++;
		
		res += cnt_xor_row[xor_col[c]];
		res += cnt_xor_col[xor_row[r]];
		if (xor_col[c] == xor_row[r]) res--;
		
	};
		
	for (int i = 0, old_r, old_c, new_r, new_c, x; i < p; ++i) {
		cin >> old_r >> old_c >> new_r >> new_c;
		change(old_r, old_c, val[{old_r, old_c}]);
		swap(val[{old_r, old_c}], val[{new_r, new_c}]); 
		change(new_r, new_c, val[{new_r, new_c}]);
		cout << n * n - res << '\n';
	}
	return 0;
}

