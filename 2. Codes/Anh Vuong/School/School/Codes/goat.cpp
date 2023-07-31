#include <bits/stdc++.h>
using namespace std;

int main() {
    double pi = atan2(0, -1);
    cout << setprecision(3) << fixed;
    int t; cin >> t;
    while (t--) {
        double n, r; cin >> n >> r;
        double res = pi * r * r; n /= 2;
        if (r * r >= n * n * 2) {
            cout << n * n * 4 << '\n';
            continue;
        }
        if (r > n) {
            double ang = acos(n / r);
            double quad = ang * r * r;
            double m = sqrt(r * r - n * n);
            quad -= m * n; res -= quad * 4;
        }
        cout << res << '\n';
    }
}