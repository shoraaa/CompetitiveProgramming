#include<bits/stdc++.h>
using namespace std;

int n, m, a, b;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin >> n >> m >> a >> b;
    int ans = ( a % m != 1 ) + ( b % m != 0);
    if ( ( a % m != 1 ) || ( b % m != 0) ) ans ++;
    cout << ans - ( b == n ) << '\n';

    if ( a % m != 1 )
    cout << ( a - 1 ) % m << ' ' << a/m << ' ' << m << ' ' << a/m + 1 << '\n';

    if ( b == n ){
        cout << 0 << ' ' << ( a % m <= 1 ? a/m : a/m + 1 ) << ' ' << m << ' ' << ( b % m == 0 ? b/m : b/m + 1 ) << '\n';
    }
    else{
        cout << 0 << ' ' << ( a % m <= 1 ? a/m : a/m + 1 ) << ' ' << m << ' ' << b/m << '\n';

        if ( b % m != 0 )
        cout << 0 << ' ' << b/m << ' ' << b%m << ' ' << b/m+1 << '\n';
    }

    return 0;
}
