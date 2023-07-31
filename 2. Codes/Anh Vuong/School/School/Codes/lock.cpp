#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

const int N = 2505;
const int inf = 0x3f3f3f3f;

int dp[2][N * 20];
char s[N], t[N];

int& f(int i, int j) {
    return dp[i & 1][j + N * 10];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, 0x3f, sizeof dp);
    f(0, 0) = 0;
    cin >> (s + 1) >> (t + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        memset(dp[i & 1], 0x3f, sizeof dp[i & 1]);
        int a = s[i] - '0', b = t[i] - '0';
        for (int j = 0; j <= 9 * (i - 1); j++) {
            int c = (b - (a + j) % 10 + 10) % 10;
            cmin(f(i, j + c), f(i - 1, j) + c);
            c = ((a - j) % 10 - b + 20) % 10;
            cmin(f(i, -(j + c)), f(i - 1, -j) + c);
        }
        for (int j = 9 * i; j > 0; j--) {
            cmin(f(i, j - 1), f(i, j));
            cmin(f(i, 1 - j), f(i, -j));
        }
    }
    cout << f(n, 0) << '\n';
}