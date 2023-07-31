#include <bits/stdc++.h>
using namespace std;
int n,k;
vector <int> D[102];
long long mod,F[52][52][52][102],lt[52],G[152][152][4][102];
string s;
void setup()
{
    lt[0]=1%k;
    for (int i=1;i<=n;i++)
        lt[i]=(10*lt[i-1])%k;
    for (int i=0;i<k;i++)
        for (int j=0;j<k;j++)
            if ((j*10)%k==i) D[i].push_back(j);
}
void solve()
{
    s=' '+s;
    memset(F,0,sizeof(F));
    int i,j,l,t;
    for (i=0;i<=n+1;i++)
    {
        for (j=0;j<=n+1;j++)
            F[i][j][0][0]=1;
        if (i>=1&&i<=n) F[i][i][1][(s[i]-48)%k]=1;
    }
    for (i=n;i>=1;i--)
        for (j=i+1;j<=n;j++)
            for (l=1;l<=j-i+1;l++)
                for (t=0;t<k;t++)
    {
        F[i][j][l][t]=F[i+1][j][l][t]+F[i][j-1][l][t]-F[i+1][j-1][l][t]+mod;
        if (s[i]==s[j])
        {
            int p=(s[i]-48)*lt[l-1]+s[i]-48;p%=k;
            int x=t-p+k;x%=k;
            for (int h=0;h<D[x].size();h++)
            {
                F[i][j][l][t]+=(F[i+1][j-1][l-2][D[x][h]]);
            }

        }
        F[i][j][l][t]%=mod;
    }
    long long res=0;
    for (l=1;l<=n;l++)
    {
        res+=F[1][n][l][0];
        res%=mod;
    }
    cout<<res;
}
void sub1()
{
    setup();
    while (cin>>s)
        solve();
}
void sub2()
{

    cin>>s;s=' '+s;
    setup();
    memset(G,0,sizeof(G));
    int i,j,l,t;
   // cout<<k<<endl;
    for (i=0;i<=n+1;i++)
    {
        for (j=0;j<=n+1;j++)
            G[i][j][0][0]=1;

        if (i<=n) G[i][i][1][(s[i]-48)%k]=1;
    }
    for (i=n;i>=1;i--)
        for (j=i+1;j<=n;j++)
            for (l=0;l<4;l++)
                for (t=0;t<k;t++)
    {
        G[i][j][l][t]=G[i+1][j][l][t]+G[i][j-1][l][t]-G[i+1][j-1][l][t]+mod;
        if (s[i]==s[j])
        {
            int p=(s[i]-48)*lt[(l-1+4)%4]+s[i]-48;p%=k;
            int x=t-p+k;x%=k;
            for (int h=0;h<D[x].size();h++)
            {
                G[i][j][l][t]+=(G[i+1][j-1][(l-2+4)%4][D[x][h]]);
            }
        }

        G[i][j][l][t]%=mod;
      // if (G[i][j][l][t]>0) cout<<i<<' '<<j<<' '<<l<<' '<<t<<' '<<G[i][j][l][t]<<endl;
    }
    long long res=0;
    for (l=0;l<4;l++)
    {
        res+=G[1][n][l][0];
        //cout<<G[1][n][l][0]<<endl;
        res%=mod;
    }
    //cout<<G[5][7][3][0]<<endl;
    cout<<res-1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("kpalin.inp","r",stdin);
    // freopen("kpalin.out","w",stdout);

    cin>>n>>k>>mod;
   // if (n<=70) sub1();
  //  else
        sub2();

}
