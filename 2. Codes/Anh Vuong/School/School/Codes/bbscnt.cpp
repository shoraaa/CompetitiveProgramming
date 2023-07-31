#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

char s[N];
int cnt[N], lst[N][26];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> (s + 1);
    int n = strlen(s + 1);
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        int j = lst[i - 1][s[i] - 'a'];
        if (j) {
            res += (cnt[i] = cnt[j - 1] + 1);
            for (int c = 0; c < 26; c++)
                lst[i][c] = lst[j - 1][c];    
        }
        lst[i][s[i] - 'a'] = i;
    }
    cout << res << '\n';
}
