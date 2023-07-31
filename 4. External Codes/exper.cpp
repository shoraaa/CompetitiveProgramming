#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

const int N = 5005;
int n, res[N];
pair < pair < int, int>, int> P[N];

int main() {
    freopen ("exper.inp", "r", stdin);
    freopen ("exper.out", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> P[i].x.x >> P[i].x.y, P[i].y = i;

    sort (P+1, P+1+n);
    for (int i = 1; i <= n; i++) {
        double Max = -INT_MAX;
        for (int j = i+1; j <= n; j++) {
            double x = (P[j].x.y - P[i].x.y) * 1.0 / (P[j].x.x - P[i].x.x);
            if (x >= Max) {
                res[P[i].y]++; res[P[j].y]++;
                Max = x;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << res[i] << '\n';
}
