#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
int n, q;
pair<int, int> val[N * 2];
vector<tuple<int, int, int, int, int, int>> query[N * 2];
int ans[N];

const int INF = 1e9;

struct SegmentTree {
  
  struct Node {
    int max[2][2];
    Node() {
      max[0][0] = max[0][1] = max[1][0] = max[1][1] = -INF;
    }
  };
  
  int n;
  vector<Node> st;
  
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) {}
  
  void merge(Node& z, Node& x, Node& y) {
    for (int x1 = 0; x1 < 2; ++x1) {
      for (int x2 = 0; x2 < 2; ++x2) {
        for (int m = 0; m < 2; ++m) {
           z.max[x1][x2] = max(z.max[x1][x2], min(x.max[x1][m], y.max[m][x2])); 
        }
      }
    }
  }
  
  int x, y, v;
  
  void update(int k, int l, int r) {
    if (l == r) {
      
      st[k].max[x][x] = v;
      st[k].max[x^1][x] = st[k].max[x][x^1] = min(st[k].max[x^1][x^1], v);

      return;
    }
    int m = (l + r) / 2;
    if (y <= m) update(k * 2, l, m);
    else update(k * 2 + 1, m + 1, r);
    merge(st[k], st[k * 2], st[k * 2 + 1]);

  }
  
  void set(int x, int y, int v) {
    this->x = x;
    this->y = y;
    this->v = v;
    update(1, 1, n);
  }
  
  
  Node ans;
  int flag;
  
  int x1, x2, y1, y2;
  
  void get(int k, int l, int r) {
    if (l > y2 || r < y1) return;
    if (l >= y1 && r <= y2) {
      if (!flag) ans = st[k], flag = 1;
      else merge(ans, ans, st[k]);
      return;
    }
    int m = (l + r) / 2;
    get(k * 2, l, m);
    get(k * 2 + 1, m + 1, r);
  }
  
  int get(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    ans = Node();
    flag = 0;
    get(1, 1, n);
    return ans.max[x1][x2];
  }
  
  
  
} st;


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  
  for (int h = 0; h < 2; ++h) {
    for (int i = 1, x; i <= n; ++i) {
      cin >> x;
      val[x] = {h, i};
    }
  }
  
  cin >> q;
  
  for (int i = 0, x1, y1, x2, y2, L, R; i < q; ++i) {
    cin >> x1 >> y1 >> x2 >> y2 >> L >> R;
    query[R].emplace_back(x1, y1, x2, y2, L, i);
  }
  
  st = SegmentTree(n);
  
  for (int x = 1; x <= n * 2; ++x) {
    int h, i;
    tie(h, i) = val[x];
    st.set(h, i, x);
    for (auto& t : query[x]) {
      int x1, y1, x2, y2, L, i;
      tie(x1, y1, x2, y2, L, i) = t;
      ans[i] = st.get(x1, y1, x2, y2) >= L;
    }
  }
  
  for (int i = 0; i < q; ++i) {
    cout << (ans[i] ? "YES\n" : "NO\n");
  }
  
	return 0;
}

