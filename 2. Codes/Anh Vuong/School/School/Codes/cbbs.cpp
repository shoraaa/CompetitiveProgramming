#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int K = 12;

int p[K][N], l[K][N];
vector <int> st[K];
char s[K][N];
int t[256], cnt[N], id[K];
map <vector <int>, deque <int>> dq;

int main() {
    int k, n;
    long long ans = 0;
    scanf("%d%d", &k, &n);
    vector <int> v;
    for (int i = 1; i <= k; i++) {
        scanf("%s", s[i] + 1);
        st[i].push_back(0);
        v.push_back(0);
    }
    dq[v].push_back(0);
    t['('] = 1; t[')'] = -1;
    for (int i = 1; i <= n; i++) {
        int li = 0; v.clear();
        for (int j = 1; j <= k; j++) {
            p[j][i] = p[j][i - 1] + t[s[j][i]];
            while (!st[j].empty()
            && p[j][st[j].back()] >= p[j][i])
                st[j].pop_back();
            if (st[j].size())
                li = max(li, st[j].back() + 1);
            st[j].push_back(i);
            v.push_back(p[j][i]);
        }
        auto it = dq.find(v);
        if (it != dq.end()) {
            while (it->second.size()
            && it->second.front() < li)
                it->second.pop_front();
            ans += it->second.size();
            it->second.push_back(i);
        }
        else dq[v].push_back(i);
    }
    printf("%lld\n", ans);
}
