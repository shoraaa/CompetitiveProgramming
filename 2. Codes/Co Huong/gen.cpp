#include<bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 15;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cout << N << '\n';
  for (int i = 0; i < N; ++i)
  	cout << rng() % N + 1 << ' ';
	return 0;
}

