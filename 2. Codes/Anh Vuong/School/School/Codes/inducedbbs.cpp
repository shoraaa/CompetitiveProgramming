#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int dp[N][N]; char s[N];

bool open(char c) {
    return c == '(' || c == '[';
}

char inv(char c) {
    if (c == '(') return ')';
    if (c == ')') return '(';
    if (c == '[') return ']';
    return '[';
}

int cal(int i, int j) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (~dp[i][j]) return dp[i][j];
    dp[i][j] = cal(i + 1, j) + 1;
    if (open(s[i])) {
        for (int k = i; k <= j; k++)
            if (s[i] == inv(s[k]))
                dp[i][j] = min(dp[i][j], cal(i + 1, k - 1) + cal(k + 1, j));
    }
    return dp[i][j];
}

void rec(int i, int j) {
    if (i > j) return;
    if (i == j) {
        if (open(s[i])) cout << s[i] << inv(s[i]);
        else cout << inv(s[i]) << s[i];
        return;
    }
    if (dp[i][j] == cal(i + 1, j) + 1) {
        rec(i, i); rec(i + 1, j); return;
    }
    if (open(s[i])) {
        for (int k = i; k <= j; k++)
            if (s[i] == inv(s[k]) && dp[i][j] == cal(i + 1, k - 1) + cal(k + 1, j)) {
                cout << s[i]; rec(i + 1, k - 1); cout << s[k]; rec(k + 1, j); return;
            }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> (s + 1)) {
        memset(dp, -1, sizeof dp);
        int n = strlen(s + 1);
        cal(1, n); rec(1, n);
        cout << '\n';
    }
}
