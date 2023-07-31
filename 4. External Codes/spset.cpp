#include <bits/stdc++.h>
using namespace std;

//void dp_naive() {
//// this dp approach is wrong
//    for (int i = 2; i < N; i++) f[1][i][0] = 1;
//    for (int i = 1; i < n; i++)
//        for (int j = 0; j < N; j++)
//            for (int k = 0; k < N; k++) {
//                if (!f[i][j][k]) continue;
//                for (int t = 2; ; t++) {
//                    int newSum = j + t;
//                    int newDif = j * (t - 1) + t * (k - 1);
//                    if (newSum >= N) break;
//                    if (newDif >= N) break;
//                    f[i+1][newSum][newDif] += f[i][j][k];
////                    cout << " from " << i << ' ' << j << ' ' << k << '\n';
////                    cout << " to " << i + 1 << ' ' << newSum << ' ' << newDif << '\n';
//                }
//            }
//
//    int res = 0;
//    for (int i = 0; i <= n; i++)
//        for (int t = 0; t < N; t++) {
//            //if (f[i][t][n-i]) cout << i << ' ' << t << ' ' << n - i << '\n';
//            res += f[i][t][n-i];
//        }
//
//    cout << res << '\n';
//
//    exit (0);
//}

#define int long long
int N;
long long btrk(int n, int x, int S, int P) {
    if (n + P - S == N) return 1;
    if (x > N) return 0;
    if (1LL * P * x - S - x + n > N) return 0;
    int mul = 1, sum = 0;
    for (int t = 0; t <= 20; t++) {
        int new_S = S + x * t;
        int new_P = P * mul;
        if (new_P - new_S + n > N) break;
        sum += btrk (n+t, x+1, new_S, new_P);
        mul *= x;
    }
    return sum;
}

main() {
    freopen ("spset.inp", "r", stdin);
    freopen ("spset.out", "w", stdout);

    cin >> N;

    //dp_naive();

    cout << btrk (0, 2, 0, 1) << '\n';

    return 0;
}
