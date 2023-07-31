#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
int a[N];
vector<int> idx[4];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i], 
		idx[a[i]].emplace_back(i);
	// dien tat ca 2 va 3 = 1
	// sau do dien 1 = 3
	// neu so 1 < so 3 thi giam dan cac 1=3 thay bang 2
	// neu so 1 > so 3 thi giam dan cac 3=1 thay bang 2
	// neu thay het 3=1->2 roi ma van ko dc -> thay dan 2=1->3
	vector<int> res(n, -1);
	for (int i : idx[2]) res[i] = 1;
	for (int i : idx[3]) res[i] = 1;
	for (int i : idx[1]) res[i] = 3;
	if (idx[2].size() + idx[3].size() < idx[1].size()) {
		int l = idx[1].size() - (idx[2].size() + idx[3].size());
		for (int i = 0; i < l; ++i) res[idx[1][i]] = 2;
	} else if (idx[2].size() + idx[3].size() > idx[1].size()) {
		//
		int need = idx[2].size() + idx[3].size() - idx[1].size();
		for (int i = 0; i < idx[3].size() && need > 0; ++i) res[idx[3][i]] = 2, need--;
		int i = 0; // need la chenh lech so luong 1 va 3 hien tai
		for (; need > 0 && i < idx[2].size(); ++i) {
			res[idx[2][i]] = 3;
			need -= 2;
		}
		if (need > 0) return cout << 0, 0;
		if (need == -1) {
			// tang luong 1 len hoac giam luong 3 di
			if (idx[1].size() > 0) res[idx[1][0]] = 2; // thay so dang = 3 thanh 2
			else if (idx[3].size() > 0) res[idx[3][0]] = 1; // thay so dang = 2 thanh 1 
			else return cout << 0, 0;	
		}
	}
	for (int i = 0; i < n; ++i)
		assert(res[i] != -1);
	for (int i = 0; i < n; ++i)
		cout << res[i] << ' ';
	return 0;
}

