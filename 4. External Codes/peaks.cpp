#include <bits/stdc++.h>
using namespace std;
int k;
long long n;
int F[1000002][32];
const int mod=239;
void solve()
{
    cin>>n>>k;
    F[1][1]=1;
    long long circle=0;
    for (int i=2;i<=1000000;i++)
    {
        for (int j=1;j<=k;j++)
        {
            F[i][j]+=2*j*F[i-1][j];
            if (i>2*(j-1)) F[i][j]+=(i-2*(j-1))*F[i-1][j-1];
            F[i][j]%=mod;
        }
        int kt=0;
        for (int j=2;j<=k;j++)
            if (F[i][j]>0) kt=1;
        if (circle==0&&kt==0&&F[i][1]==1)
        {
            circle=i-1;
            break;
        }
    }
    //cout<<circle<<endl;
    cout<<F[n%circle][k];
}
int main()
{
    freopen("peaks.inp","r",stdin);
    freopen("peaks.out","w",stdout);
    solve();
}
