#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second
#define eb emplace_back

using ll = long long;

int orient(pii a, pii b, pii c) {
  return a.fi*(b.se-c.se) + b.fi*(c.se-a.se) + c.fi*(a.se-b.se);
}

ll sqr(ll x) {
  return x * x;
}

ll sqd(pii a, pii b) {
  return sqr(a.fi - b.fi) + sqr(a.se - b.se);
}

int check(vector<pii> p) {
  bool hasPos=false, hasNeg=false;
  for (int i=0, n=p.size(); i<n; i++) {
    int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
   // assert(o != 0);
    if (o > 0) hasPos = true;
    if (o < 0) hasNeg = true;
    
    ll squaredDis = sqd(p[i], p[(i+1)%n]);
    ll root = sqrt(squaredDis);
    if (root * root != squaredDis) return 0;
    
  }
  return !(hasPos && hasNeg);
}

int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; int nn = (n + 3) / 4 * 4, rem = nn - n;
	if (n <= 2) return cout << "NO", 0;
	else if (n == 3) return cout << "YES\n0 0\n0 3\n4 0", 0;
	else if (n == 4) return cout << "YES\n0 0\n0 4\n4 4\n4 0", 0;
	vector<pii> point;
	int x = 0, y = 0;
	x += 25;
	if (rem) rem--;
	else point.eb(x, y);
	for (int i = 1; i <= nn / 4 - 1; ++i) {
		x += 7; y += 24;
		point.eb(x, y);
	}	
	y += 25; 
	if (rem) rem--;
	else point.eb(x, y);
	for (int i = 1; i <= nn / 4 - 1; ++i) {
		x -= 24; y += 7;
		point.eb(x, y);
	}
	x -= 25; 
	if (rem) rem--;
	else point.eb(x, y);
	for (int i = 1; i <= nn / 4 - 1; ++i) {
		x -= 7; y -= 24;
		point.eb(x, y);
	}
	y -= 25; 
	if (rem) rem--;
	else point.eb(x, y);
	for (int i = 1; i <= nn / 4 - 1; ++i) {
		x += 24; y -= 7;
		point.eb(x, y);
	}
	cout << "YES\n";
	reverse(point.begin(), point.end());
	for (pii &v : point) cout << '(' << v.fi << ',' << v.se << ')' << '\n';
	
	assert(check(point));
	
	return 0;
}

