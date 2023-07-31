#include <bits/stdc++.h>
using namespace std;

const int N = 2000005;

using ll = long long;

ll p[N], h[N], s[N], sh[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i]; p[i]++;
    }
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        sh[i] = sh[i - 1] + h[i];
    }
    stack <int> st; st.push(0);
    for (int i = 1; i <= n; i++) {
        while (st.top() && h[st.top()] < h[i])
            st.pop();
        s[i] = s[st.top()] - sh[i] + sh[st.top()]
        + (p[i] - p[st.top()]) * h[i];
        st.push(i);
    }
    
    int q; cin >> q;
    while (q--) {
        ll k; cin >> k;
        int lo = 0, hi = n;
        while (lo < hi) {
            int mi = (lo + hi + 1) / 2;
            if (s[mi] < k) lo = mi;
            else hi = mi - 1;
        }
        cout << lo << '\n';
    }
}