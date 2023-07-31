#include<bits/stdc++.h>
using namespace std;
using ll = long long;

using T = long double;
using P = complex<T>;
#define x real()
#define y imag()

T cross(P a, P b) { return (conj(a) * b).y; }
T orient(P a, P b, P c) { return cross(b - a, c - a); }
T area(P a, P b, P c) { return abs(orient(a, b, c)) / 2.0; }

const int N = 1e6 + 5;
P a[N]; T p[N]; int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; 
  T res = 0, cY = 0.0; p[0] = 0;
  for (int i = 1; i <= n; ++i) 
    cin >> p[i];
  for (int i = 0; i <= n; ++i) 
    cY += p[i], a[i] = {T(i), T(cY)};
  vector<P> st; 
  for (int i = 0; i <= n; ++i) {
    while (st.size() >= 2 && orient(st[st.size() - 2], st.back(), a[i]) < 0)
      res += area(st[st.size() - 2], st.back(), a[i]), st.pop_back();
    st.push_back(a[i]);
  }
  cout << fixed << setprecision(1) << res << '\n';
	return 0;
}
