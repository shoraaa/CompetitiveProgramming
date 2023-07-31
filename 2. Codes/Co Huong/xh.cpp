#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Box {
  ll x, y, h;
  Box() = default;
  Box(ll x, ll y, ll h): x(x), y(y), h(h) {}
};
struct Cylinder {
  ll r, h;
  Cylinder() = default;
  Cylinder(ll r, ll h): r(r), h(h) {}
};

bool operator < (Box& a, Box& b) {
  return a.x < b.x && a.y < b.y; 
}
bool operator < (Cylinder& a, Cylinder& b) {
  return a.r < b.r;
}
bool operator < (Box& a, Cylinder& b) {
  return a.x * a.x < 2 * b.r * b.r && a.y * a.y < 2 * b.r * b.r;
}
bool operator < (Cylinder& a, Box& b) {
  return a.r < b.x && a.r < b.y;
}

vector<Box> b;
vector<Cylinder> c;

const int N = 1e3 + 5;
ll dp1[N], dp2[N];
int n, m;


ll call1(int i);

ll call2(int i) {
  if (~dp2[i]) return dp2[i];
  ll res = 0;
  for (int j = 0; j < n; ++j) 
    if (c[i] < b[j]) res = max(res, call1(j));
  for (int j = 0; j < m; ++j)
    if (c[i] < c[j]) res = max(res, call2(j));
  return dp2[i] = res + c[i].h;
}

ll call1(int i) {
  if (~dp1[i]) return dp1[i];
  ll res = 0;
  for (int j = 0; j < n; ++j)
    if (b[i] < b[j]) res = max(res, call1(j));
  for (int j = 0; j < m; ++j)
    if (b[i] < c[j]) res = max(res, call2(j));
  return dp1[i] = res + b[i].h;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("xh.inp", "r"))
    freopen("xh.inp", "r", stdin),
    freopen("xh.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0, x, y, z; i < n; ++i) {
    cin >> x >> y >> z;
    b.emplace_back(x, y, z);
    b.emplace_back(y, x, z);
    b.emplace_back(x, z, y);
    b.emplace_back(z, x, y);
    b.emplace_back(y, z, x);
    b.emplace_back(z, y, x);
  }
  n = b.size();
  for (int i = 0, r, h; i < m; ++i) {
    cin >> r >> h;
    c.emplace_back(r, h);
  }
  ll res = 0;
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
  for (int i = 0; i < n; ++i)
    res = max(res, call1(i));
  for (int i = 0; i < m; ++i)
    res = max(res, call2(i));
  cout << res;
	return 0;
}

