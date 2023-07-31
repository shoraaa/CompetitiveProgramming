#include <bits/stdc++.h>
using namespace std;

const int N = 3e4 + 5;
int n;
long long s[N];
unordered_map < long long, int > cnt;

int main() {
    freopen ("stgame.inp", "r", stdin);
    freopen ("stgame.out", "w", stdout);

    scanf ("%d", &n);
    for (int i = 1, a; i <= n; i++) {
        scanf ("%d", &a);
        s[i] = s[i-1] + a;
    }

    for (int i = n; i >= 1; i--) if (s[n] % i == 0) {
        long long eachPart = s[n] / i;
        cnt.clear();
        for (int j = 1; j <= n; j++) cnt[s[j] % eachPart]++;
        for (auto it : cnt) if (it.second == i) {
            cout << n - i << '\n';
            return 0;
        }
    }

    return 0;
}
