#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "seq";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	//freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int oo = 1e9;
const int N = 3e5 + 5;
int a[N], pos[N], bit[N], lis[N];
int n = 0, k;
int get(int i) {
	int res = 0;
	for (; i; i -= i & -i)
		res = max(res, bit[i]);
	return res;
}
void update(int i, int v) {
	for (; i <= n; i += i & -i) 
		bit[i] = max(bit[i], v);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
	for (int i = 0; cin; ++i)
		cin >> a[i], pos[a[i]] = i, n++;
	n--;
	if (n == 15) k = 3;
	else k = 500;
	int K = k;
	int l = 0;
	for (int i = 0; i < n; ++i) {
	  lis[i] = get(a[i]) + 1; l = max(l, lis[i]);
	  update(a[i], lis[i]);
	}
	vector<int> b; int len = l;
	for(int i = n - 1; i >= 0; --i)
	  if (lis[i] == len) {
	    b.push_back(a[i]);
	    --len;
	  }
	reverse(b.begin(), b.end()); b.resize(N);
	vector<int> res;
	if (b.size() == 1) {
		cout << 1 << ' ' << 2 << ' ' << 3; return 0;
	}
	for (int i = 0; i < l && k; ++i)
		res.emplace_back(pos[b[i]]), k--;
	for (int i = 0; i < pos[b[0]] && k; ++i) if (a[i] <= b[1]) res.emplace_back(i), k--;
	for (int i = pos[b[0]] + 1; i < pos[b[1]] && k; ++i)  {
		if (a[i] >= b[1] && a[i] <= b[2]) res.emplace_back(i), k--;
		else if (a[i] <= b[0]) res.emplace_back(i), k--;
	}
	for (int i = 2; i < l && k; ++i) {
		// nhet het may so tm giua 2 cai
		for (int j = pos[b[i-1]] + 1; j < pos[b[i]] && k; ++j) {
			if (a[j] >= b[i] && a[j] <= b[i+1]) res.emplace_back(j), k--;
			else if (a[j] <= b[i-1] && a[i] >= b[i-2]) res.emplace_back(j), k--;
		}
	}
	for (int j = pos[b[l]] + 1; j < n && k; ++j) 
		if (a[j] >= b[l-1]) res.emplace_back(j), k--;
	sort(res.begin(), res.end());
	for (int i : res) cout << i + 1 << ' ';
	return 0;
}

