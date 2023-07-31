#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;

int n, k;

#define fi first
#define se second

priority_queue<int> L, R;
ll f[N], cur = 0, sumL = 0, sumR = 0;

void insert(int x) {
  if (L.empty() || x <= L.top()) {
    L.emplace(+x);
    sumL += x;
  } else {
    R.emplace(-x);
    sumR += x;
  }
  
  if (L.size() > R.size() + 1) {
    int x = L.top();
    
    R.emplace(-x);
    sumR += x;
    
    L.pop();
    sumL -= x;
  }
  
  if (L.size() < R.size()) {
    int x = -R.top();
    
    L.emplace(x);
    sumL += x;
    
    R.pop();
    sumR -= x;
  }
  
  // Ltop*Lsize - sum_l + sum_r - Ltop*Rsize
  // = L.top() * (L.size() - R.size()) + sumR - sumL
  cur = L.top() * (L.size() - R.size()) + sumR - sumL;
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  cin >> k >> n;
  
  char p, q;
  
  vector<pair<int, int>> vec;
  ll same = 0;
  
  for (int i = 1, s, t; i <= n; ++i) {
    cin >> p >> s >> q >> t;
    if (p == q) {
      same += abs(s - t);
    } else {
      same += 1;
      vec.emplace_back(s, t);
    }
  }
  
  sort(vec.begin(), vec.end(), [](pair<int, int>& u, pair<int, int>& v) {
    return u.fi + u.se < v.fi + v.se;
  });
  
  for (int i = 0; i < vec.size(); ++i) {
    insert(vec[i].fi);
    insert(vec[i].se);
    f[i] = cur;
  }
  
  if (k == 1) {
    cout << cur + same;
    return 0;
  }
  
  ll res = cur;
  
  L = R = priority_queue<int>();
  cur = sumR = sumL = 0;
  
  for (int i = (int)vec.size() - 1; i >= 1; --i) {
    insert(vec[i].fi);
    insert(vec[i].se);
    res = min(res, f[i - 1] + cur);
  }
  
  cout << res + same;
  
	return 0;
}

