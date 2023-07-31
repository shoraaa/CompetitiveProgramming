#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
random_device rd;
mt19937 rng(rd());
const int N = 100;
char c[3] = {'R', 'G', 'W'};
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cout << N << ' ' << N << '\n';
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) 
			cout << c[rng() % 3];
		cout << '\n';
	}
	return 0;
}

