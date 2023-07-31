#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int a[N], l[N], r[N];
long long s[N];

int main() {
    freopen("pilot.in", "r", stdin);
    freopen("pilot.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    stack <int, vector <int>> st;
    st.emplace(0);
    for (int i = 1; i <= n; i++) {
        while (st.size() > 1 && a[st.top()] <= a[i])
            st.pop();
        l[i] = st.top(); st.emplace(i);
    }
    while (st.size()) st.pop();
    st.emplace(n + 1);
    for (int i = n; i > 0; i--) {
        while (st.size() > 1 && a[st.top()] < a[i])
            st.pop();
        r[i] = st.top(); st.emplace(i);
    }
    for (int i = 1; i <= n; i++)
        s[a[i]] += 1ll * (i - l[i]) * (r[i] - i);
    for (int i = 1; i < N; i++) s[i] += s[i - 1];
    while (q--) {
        int y; cin >> y; cout << s[y] << '\n';
    }
}