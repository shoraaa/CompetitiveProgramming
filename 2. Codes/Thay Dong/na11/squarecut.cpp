#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4005;
int a[N], b[N];
int n, m;

using T = long double;
const T eps = 1e-9;

using pt = complex<T>;
#define x real()
#define y imag()

T cross(pt v, pt w) { return (conj(v)*w).y; }
T orient(pt a, pt b, pt c) { return cross(b-a,c-a); }

pt p[N];

int in_range(int l, int r, int p) {
  return l <= p && p <= r;
}

int intersect(int i, int j) {
  if (a[i] == a[j] || a[i] == b[j] || b[i] == a[j] || b[i] == b[j]) return 0;
  return (in_range(a[i], b[i], a[j]) && !in_range(a[i], b[i], b[j]))
      || (in_range(a[i], b[i], b[j]) && !in_range(a[i], b[i], a[j]));
}

void intersection(int i, int j, pt &out) {
  pt A = p[a[i]], B = p[b[i]], C = p[a[j]], D = p[b[j]];
  T oa = orient(C, D, A), ob = orient(C, D, B);
  out = (A*ob - B*oa) / (ob - oa);
}

const T PI = acos(-1);

bool cmp(pt a, pt b) {
  return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;

  for (int i = 1; i <= n; ++i)
    p[i] = {0, T(i) - 1};
  for (int i = n + 1; i <= n * 2; ++i)
    p[i] = {i - T(n) - 1, T(n)};
  for (int i = n * 2 + 1; i <= n * 3; ++i)
    p[i] = {T(n), T(n) + 1 - (i - n * 2)};
  for (int i = n * 3 + 1; i <= n * 4; ++i)
    p[i] = {T(n) + 1 - (i - n * 3), 0};

  int f = 1; 
  for (int i = 0; i < m; ++i) {
    cin >> a[i] >> b[i];
    if (a[i] > b[i]) swap(a[i], b[i]);

    vector<pt> s; pt out;
    for (int j = i - 1; ~j; --j) if (intersect(i, j))
      intersection(i, j, out), s.emplace_back(out);
    
    vector<int> vis(s.size()); int ans = 0;
    for (int i = 0; i < s.size(); ++i) if (!vis[i]) {
      ans++;
      for (int j = i + 1; j < s.size(); ++j) if (cmp(s[i], s[j])) vis[j] = 1;
    }
    f += ans + 1;
  }
  cout << f;
	return 0;
}
