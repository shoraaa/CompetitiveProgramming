#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
bitset <N> bs;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--){
        bs.reset();
        bs[0] = 1; int n, q; cin >> n;
        for (int i = 1, x; i <= n; i++){
            cin >> x; bs |= bs << x;
        }
        cin >> q;
        while (q--){
            int x; cin >> x; cout << bs[x];
        }
        cout << '\n';
    }
}