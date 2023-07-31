#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 505;
int A[N][N][N], D[N][N][N];
 
const int M = 1e9 + 7;
void add(int& x, int y) { x += y; if (x >= M) x -= M; }
void sub(int& x, int y) { x -= y; if (x < 0) x += M; }
int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }
 
int n, s, t;
 
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s >> t; 
  
  A[2][1][2] = D[2][2][1] = 1;
  for (int i = 3; i <= n; ++i) {
    for (int t = 1; t <= i; ++t) {
      
      for (int j = 1; j <= i - 1; ++j) {
        add(A[i][1][t], D[i - 1][j][t - 1]);
      }
      for (int s = 2; s <= t - 1; ++s) {
        A[i][s][t] = dif(A[i][s - 1][t], D[i - 1][s - 1][t - 1]);
        D[i][s][t] = sum(D[i][s - 1][t], A[i - 1][s - 1][t - 1]);
      }
      
      for (int j = 1; j <= i - 1; ++j) {
        add(D[i][i][t], A[i - 1][j][t]);
      }
      for (int s = i - 1; s >= t + 1; --s) {
        A[i][s][t] = sum(A[i][s + 1][t], D[i - 1][s][t]);
        D[i][s][t] = dif(D[i][s + 1][t], A[i - 1][s][t]);
      }
      
    }
  }
  
  add(A[n][s][t], D[n][s][t]);
  cout << A[n][s][t];
 
	return 0;
}