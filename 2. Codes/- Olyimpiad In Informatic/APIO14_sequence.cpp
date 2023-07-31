#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const ll INF = 1e18;

int a[N]; ll f[N];
ll dp[2][N];
int path[205][N];

#define fi first
#define se second

int n, m;

struct Line {
  ll a, b;
  int i;
  Line() = default;
  Line(ll a, ll b, int i): a(a), b(b), i(i) {}
  ll get(int x) {
    return a * x + b;
  }
} dq[N];
int front, back;

using ld = long double;

int better(const Line& a, const Line& b, const Line& c) {
  // (a1-a2) * x = b2-b1
  // x = (b2 - b1) / (a1 - a2)
  return (a.b - b.b) * (a.a - c.a) >= (a.b - c.b) * (a.a - b.a);
}

void insert(ll a, ll b, int i) {
  Line l(a, b, i);
  while (back > front && better(l, dq[back], dq[back - 1])) {
    back--;
  }
  dq[++back] = l;
}

pair<ll, int> get(int x) {
  while (front < back && dq[front].get(x) <= dq[front + 1].get(x)) {
    front++;
  }
  return make_pair(dq[front].get(x), dq[front].i);
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  cin >> n >> m; m++;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    f[i] = f[i - 1] + a[i];
  }
  
  // if (n <= 1000) {
    // task1();
    // return 0;
  // }
  
  for (int k = 2; k <= m; ++k) {
    int cu = k & 1, pr = cu ^ 1;
    front = 0, back = -1;
    for (int i = 1; i <= n; ++i) {
      // sum = f[j] * f[i] + dp[k - 1][j].fi - f[j] * f[j];
      insert(f[i - 1], dp[pr][i - 1] - f[i - 1] * f[i - 1], i - 1);
      auto val = get(f[i]);
      dp[cu][i] = val.fi;
      path[k][i] = val.se;
    }
  }
  
  cout << dp[m & 1][n] << '\n';
  int i = m, j = n;
  while (i > 1) {
    cout << path[i][j] << ' ';
    j = path[i][j]; i--;
  }
  
	return 0;
}

