#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

char s[N][N];
int a[N][N], dp[N];

long long solve(int n, char c) {
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        stack <int> st; st.push(0);
        for (int j = 1; j <= n; j++) {
            if (s[i][j] < c)
                a[i][j] = a[i - 1][j] + 1;
            else a[i][j] = 0;
            dp[j] = 0;
            if (!a[i][j]) {
                while (a[i][st.top()] > a[i - 1][j])
                    st.pop();
                if (s[i][j] == c && a[i - 1][j])
                    res += dp[st.top()];
                while (st.top()) st.pop();
            }
            else {
                while (a[i][st.top()] >= a[i][j])
                    st.pop();
                dp[j] = dp[st.top()] + 1;
                st.push(j);
            }
        }
    }
    for (int i = n; i > 0; i--) {
        stack <int> st; st.push(n + 1);
        for (int j = n; j > 0; j--) {
            if (s[i][j] < c)
                a[i][j] = a[i + 1][j] + 1;
            else a[i][j] = 0;
            dp[j] = 0;
            if (!a[i][j]) {
                while (a[i][st.top()] > a[i + 1][j])
                    st.pop();
                if (s[i][j] == c && a[i + 1][j])
                    res += dp[st.top()];
                while (st.top() <= n) st.pop();
            }
            else {
                while (a[i][st.top()] >= a[i][j])
                    st.pop();
                dp[j] = dp[st.top()] +
                (s[i + a[i][j]][j] != c);
                st.push(j);
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    long long res = 0;
    for (int i = 1; i <= n; i++)
        cin >> (s[i] + 1);
    for (char c = 'a'; c <= 'z'; c++)
        res += solve(n, c);
    cout << res << '\n';
}