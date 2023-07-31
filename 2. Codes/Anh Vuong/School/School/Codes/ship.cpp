#include <bits/stdc++.h>
using namespace std;

bitset <505> a[505], b[505], c[505];
int n, m, cnt = 0;

void update(char x){
    if (x == 'W')
        for (int i = 1; i <= n; i++)
            b[i] = a[i] & (b[i] >> 1);
    if (x == 'E')
        for (int i = 1; i <= n; i++)
            b[i] = a[i] & (b[i] << 1);
    if (x == 'S')
        for (int i = n; i >= 1; i--)
            b[i] = a[i] & b[i - 1];
    if (x == 'N')
        for (int i = 1; i <= n; i++)
            b[i] = a[i] & b[i + 1];
    if (x == '?'){
        for (int i = 1; i <= n; i++){
            c[i] = (b[i] >> 1) | (b[i] << 1);
        }
        for (int i = n; i >= 1; i--) c[i] |= b[i - 1];
        for (int i = 1; i <= n; i++) c[i] |= b[i + 1];
        for (int i = 1; i <= n; i++) b[i] = c[i] & a[i];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m; int t; cin >> t;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            char x; cin >> x;
            if (x == '.'){
                a[i][j] = 1; b[i][j] = 1;
            }
       }
    string cmd; cin >> cmd;
    for (char x : cmd) update(x);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (b[i][j]) cnt++;
    cout << cnt << '\n';
}