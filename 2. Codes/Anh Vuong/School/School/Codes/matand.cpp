#include <bits/stdc++.h>
using namespace std;

const int N = 505;
int a[N][N], b[N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, x, res = 0; cin >> n >> x;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++)
    {
        for (int k = 1; k <= n; k++) 
            b[k] = -1;
        
        for (int j = i; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
                b[k] &= a[j][k];
            
            for (int k = 1; k <= n; k++)
            {
                int l = k, cur = -1;
                while (l <= n && (cur & b[l] & x) == x)
                {
                    cur &= b[l]; l++;
                    if (cur == x)
                        res = max(res, (j - i + 1) * (l - k));
                }
                k = l;
            }
        }
    }
    cout << res << '\n';
}