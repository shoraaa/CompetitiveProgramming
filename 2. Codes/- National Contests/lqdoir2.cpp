#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int M = 1e9 + 7;
double n;
double sqr(double x) {
  return x * x;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("numcities.inp", "r"))
    freopen("numcities.inp", "r", stdin),
    freopen("numcities.out", "w", stdout);
  int T; cin >> T;
  while (T--) {
    cin >> n;
    double res = sqr(floor(sqrt(n))); 
    res = res * (sqr(1+floor(sqrt(n)))/4.0-n-1);
    for (int i = 1; i <= floor(sqrt(n)); ++i) 
      res += floor(n/i) * (2*n+2-i*(1+floor(n/i)));
    res += n + 1;
    res = fmod(res, M);
    printf("%.0f\n", res);
  }
	return 0;
}

