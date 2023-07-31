#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, inf = 2e9;
struct Segment {
  int l, r, i;
  Segment(int l, int r, int i): l(l), r(r), i(i) {}
  bool operator < (const Segment& s) const {
    if (l == s.l) return r < s.r;
    return l < s.l;
  }
};
int ans[N];
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    vector<pair<int, int>> que;
    vector<Segment> seg; 
    vector<int> used(n + 1); map<int, int> cnt;
    for (int i = 1, l, r; i <= n; ++i)
      cin >> l >> r, 
      que.emplace_back(l, -i),
      que.emplace_back(r, i),
      seg.emplace_back(l, r, i),
      cnt[l]++;
    memset(ans, 0, sizeof(ans));
    int res = 0, l = -inf, r = -inf;
    sort(seg.begin(), seg.end());
    for (auto& s : seg) {
      if (s.l > r) 
        res++, used[s.i] = 1,
        l = s.l, r = s.r;
      else r = max(r, s.r);
    } 
    for (auto& s : seg)
      if (used[s.i] && cnt[s.l] == 1) ans[s.i]--;
    sort(que.begin(), que.end());
    set<int> st;
    for (int i = 0; i < que.size(); ) {
      int p = que[i].first, j = i;
      vector<int> op, cl;
      while (j < que.size() && que[j].first == p) {
        if (que[j].second < 0) op.emplace_back(-que[j].second);
        else cl.emplace_back(que[j].second);
        j++;
      } 
      i = j;
      if (st.size() == 1 && !op.empty())
        ans[*st.begin()]++;
      for (int i : op) st.insert(i);
      for (int i : cl) st.erase(i);
    } 
    cout << *max_element(ans + 1, ans + n + 1) + res << '\n';
    
    
  }
	return 0;
}

