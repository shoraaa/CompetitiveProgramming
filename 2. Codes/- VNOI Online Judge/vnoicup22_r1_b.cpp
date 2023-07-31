	#include<bits/stdc++.h>
	using namespace std;
	using ll = long long;
	void file() {
		const string FILE_NAME = "FILE_NAME";
		freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
		freopen((FILE_NAME + ".out").c_str(), "w", stdout);
	}
	const int N = 2e6 + 5;
	int a[N], boi[N], cnt[N];
	ll calc(int x) {
		ll n = boi[x];
		return ll(n) * (n-1) / 2;
	}
	int n;
	int main() {
		cin.tie(0)->sync_with_stdio(0); cout.tie(0);
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> a[i], cnt[a[i]]++;
		for (int i = 1; i < N; ++i)
			for (int j = i; j < N; j += i)
				boi[i] += cnt[j];
		for (int i = 0; i < n; ++i)
			cout << calc(a[i] * 2) << ' '; 
		
		return 0;
	}
	
	