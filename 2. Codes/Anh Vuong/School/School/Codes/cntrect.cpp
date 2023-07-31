#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

char s[N]; int a[N], l[N], r[N];

long long cal(int w, int h) {
    return 1ll * w * (w + 1) / 2 * h;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector <int> st;
    long long res = 0;
    while (n--) {
        cin >> (s + 1);
        for (int i = 1; i <= m; i++)
            if (s[i] == '1') a[i]++;
            else a[i] = 0;
        st.clear(); st.push_back(0);
        for (int i = 1; i <= m; i++) {
            while (st.back() && a[st.back()] >= a[i])
                st.pop_back();
            l[i] = st.back() + 1;
            st.push_back(i);
        }
        st.clear(); st.push_back(m + 1);
        for (int i = m; i > 0; i--) {
            while (st.back() <= m && a[st.back()] > a[i])
                st.pop_back();
            r[i] = st.back() - 1;
            st.push_back(i);
        }
        for (int i = 1; i <= m; i++) {
            res += cal(r[i] - l[i] + 1, a[i]);
            res -= cal(r[i] - i, a[i]);
            res -= cal(i - l[i], a[i]);
        }
    }
    cout << res << '\n';
}