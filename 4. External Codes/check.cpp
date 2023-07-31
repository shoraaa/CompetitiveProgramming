#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
int a[N][N], val[N];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
  	for (int j = 1; j <= m; ++j) {
  		cin >> a[i][j];
		}
	}
	int res = 0;
	for (int x1 = 1; x1 <= n; ++x1) {
		
		
		for (int i = 1; i <= m; ++i) {
			int mx = 0;
			
			res++;
			
			for (int j = i + 1; j <= m; ++j) {
				
				res += mx < min(a[x1][i], a[x1][j]);
				mx = max(mx, a[x1][j]);
				
			}
		}
		
		
		
		
		for (int i = 1; i <= m; ++i) val[i] = 0;
		
		for (int x2 = x1 + 1; x2 <= n; ++x2) {
			
			for (int i = 1; i <= m; ++i) {
				val[i] = max(val[i], a[x2][i]);
			}
			
			for (int i = 1; i <= m; ++i) {
				int mx = 0;
				
				for (int h = x1 + 1; h <= x2 - 1; ++h) mx = max(mx, a[h][i]);
				
				res += mx < min(a[x1][i], a[x2][i]);
				mx = max(mx, a[x2][i]);
				
				for (int j = i + 1; j <= m; ++j) {
					
					for (int h = x1; h <= x2 - 1; ++h) mx = max(mx, a[h][j]);
					res += mx < min(a[x1][i], a[x2][j]);
					mx = max(mx, a[x2][j]);
					
				}
			}
			
		}
	}
	cout << res;
	
  
	return 0;
}


