#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        if (!((x ^ y) & 1)) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        while (1) {
            if (!x && abs(y) == 1) {
                cout << (y < 0 ? 'S' : 'N');
                break;
            }
            if (!y && abs(x) == 1) {
                cout << (x < 0 ? 'W' : 'E');
                break;
            }
            if (x & 1) {
                y /= 2;
                if (((x - 1) / 2 ^ y) & 1) {
                    cout << 'E';
                    x = (x - 1) / 2;
                }
                else {
                    cout << 'W';
                    x = (x + 1) / 2;
                }
            }
            else {
                x /= 2;
                if (((y - 1) / 2 ^ x) & 1) {
                    cout << 'N';
                    y = (y - 1) / 2;
                }
                else {
                    cout << 'S';
                    y = (y + 1) / 2;
                }
            }
        }
        cout << '\n';
    }
}