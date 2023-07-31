#include <bits/stdc++.h>
using namespace std;
int t,m,n,c,k;
const long long mod=1e9+7;
long long C[2][1002],R[2][1002],S[1002];
long long mpow(int a,int k)
{
    if (k==0) return 1;
    long long ans=mpow(a,k/2);
    ans*=ans;ans%=mod;
    if (k%2==1) ans*=a;ans%=mod;
    return ans;
}
void solve()
{
    cin>>c>>m>>n>>k;
    memset(S,0,sizeof(S));
    memset(C,0,sizeof(C));
    memset(R,0,sizeof(R));
    for (int i=1;i<=m;i++)
    {
        R[0][i]=mpow(i,c)-mpow(i-1,c)+mod;R[0][i]%=mod;
        R[1][i]=mpow(m-i+1,c)-mpow(m-i,c)+mod;R[1][i]%=mod;
    }
    for (int i=1;i<=n;i++)
    {
        C[0][i]=mpow(i,c)-mpow(i-1,c)+mod;C[0][i]%=mod;
        C[1][i]=mpow(n-i+1,c)-mpow(n-i,c)+mod;C[1][i]%=mod;
    }
    for (int i=1;i<=n;i++)
        for (int j=i;j<=n;j++)
    {
        S[j-i+1]+=C[0][i]*C[1][j];
        S[j-i+1]%=mod;
    }
    for (int i=n;i>=1;i--)
    {
        S[i]+=S[i+1];
        S[i]%=mod;
    }
    long long res=0;
    for (int i=1;i<=m;i++)
        for (int j=i;j<=m;j++)
    {
        int x=(k+j-i)/(j-i+1);

        if (x<=n)
        {
            long long t=S[x];
            t*=R[0][i];t%=mod;t*=R[1][j];t%=mod;
            res+=t;res%=mod;

        }
      //  cout<<i<<' '<<j<<' '<<' '<<x<<' '<<S[x]<<endl;
    }
    cout<<res<<'\n';

}
int main()
{
    freopen("paper.inp","r",stdin);
    freopen("paper.out","w",stdout);
    cin>>t;
    while (t--) solve();
}
