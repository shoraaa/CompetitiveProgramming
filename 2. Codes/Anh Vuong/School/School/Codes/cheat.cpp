#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

const int N = 100005;

int a[N], b[N], n, l[N], r[N], p[N];
vector <int> vals;

namespace subtask1 {
    void solve() {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            bool app = 0; int j = i;
            while (j <= n && a[j] <= b[1])
                if (a[j++] == b[1]) app = 1;
            if (app) res += j - i; i = j;
        }
        cout << res << '\n'; exit(0);
    }
};

namespace subtask2 {
    int dp[5005][5005];

    void solve() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (a[i] == b[j] &&
                l[i] < j && j < r[i])
                    dp[i][j] = dp[i][j - 1] + 1;
                cmax(dp[i][j], dp[i - 1][j]);
                cmax(dp[i][j], dp[i][j - 1]);
            }
        cout << dp[n][n] << '\n'; exit(0);
    }
};

namespace subtask3 {
    void solve() {
        vector <int> lis;
        for (int i = 1; i <= n; i++) {
            int j = p[b[i]];
            if (j > 0 && l[j] < i && i < r[j]) {
                auto it = upper_bound
                (lis.begin(), lis.end(), j);
                if (it == lis.end())
                    lis.push_back(j);
                else *it = j;
            }
        }
        cout << lis.size() << '\n'; exit(0);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; vals.push_back(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i]; vals.push_back(b[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(),
    vals.end()), vals.end());
    for (int i = 1; i <= n; i++) {
        a[i] = upper_bound(vals.begin(),
        vals.end(), a[i]) - vals.begin();
        p[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        b[i] = upper_bound(vals.begin(),
        vals.end(), b[i]) - vals.begin();
    vector <int> st; st.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (st.size() > 1 &&
        a[i] >= a[st.back()])
            st.pop_back();
        l[i] = st.back(); st.push_back(i);
    }
    st.clear(); st.push_back(n + 1);
    for (int i = n; i > 0; i--) {
        while (st.size() > 1 &&
        a[i] >= a[st.back()])
            st.pop_back();
        r[i] = st.back(); st.push_back(i);
    }
    if (count(b + 1, b + n + 1, b[1]) == n)
        subtask1::solve();
    if (n <= 5000) subtask2::solve();
    subtask3::solve();
}