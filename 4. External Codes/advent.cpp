#include <bits/stdc++.h>
using namespace std;
struct man
{
   int h,l;
    bool operator < (const man&a)
    const
    {
        return (h+l<a.h+a.l);
    }
};
int n;
long long d,F[2002][2002],B[2002];
man A[2002];
void solve()
{
    cin>>n;
    B[0]=0;
    for (int i=1;i<=n;i++)
    {
        cin>>A[i].h>>A[i].l;

    }
    cin>>d;
    sort(A+1,A+n+1);
    memset(F,-1,sizeof(F));
    F[0][0]=0;
    for (int i=1;i<=n;i++)
    {
        B[i]=B[i-1]+A[i].h;
        F[i][0]=B[i];
    }
    int res=0;
    for (int i=1;i<=n;i++)
        for (int j=0;j<=n;j++)
        {
            if (F[i-1][j]>=0) F[i][j]=max(F[i][j],F[i-1][j]+A[i].h);
            if (F[i-1][j-1]+B[n]-B[i-1]+A[i].l>=d)
                F[i][j]=max(F[i][j],F[i-1][j-1]);
           // cout<<i<<' '<<j<<' '<<F[i][j]<<' '<<A[i].h<<' '<<A[i].l<<endl;
            if (F[i][j]>=0) res=max(res,j);
        }
    cout<<res;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("advent.inp","r",stdin);
    freopen("advent.out","w",stdout);
    solve();
}
