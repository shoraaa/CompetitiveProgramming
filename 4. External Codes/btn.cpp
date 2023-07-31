#include <bits/stdc++.h>
using namespace std;
int n,k;
int code[256];
string s;
long long F[102][102][52],P[102][102][52],kt[102][102][52];
int check_mo(char x)
{
    if (x=='('||x=='['||x=='{'||x=='?') return 1;
    return 0;
}
int check_dong(char x)
{
    if (x==')'||x==']'||x=='}'||x=='?') return 1;
    return 0;
}
void solve()
{
    cin>>n>>k;
    cin>>s;s=' '+s;
    code['(']=1;code[')']=-1;
    code['[']=2;code[']']=-2;
    code['{']=3;code['}']=-3;
    code['?']=0;
    memset(F,0,sizeof(F));
    memset(P,0,sizeof(P));
    memset(kt,0,sizeof(kt));
    for (int i=1;i<=n+1;i++)
        for (int l=0;l<=k;l++)
        F[i][i-1][l]=1;
    for (int i=n;i>=1;i--)
        if (check_mo(s[i]))
        for (int j=i+1;j<=n;j++)
        if (check_dong(s[j]))
            for (int l=1;l<=k;l++)
        {
            F[i][j][l]=0;
            for (int p=i+1;p<j;p++)
            {
                if (check_dong(s[p]))
                {
                    if (s[i]==s[p]&&s[i]=='?')
                        F[i][j][l]+=3*F[i+1][p-1][l-1]*F[p+1][j][l];
                    if (code[s[i]]>0&&code[s[i]]+code[s[p]]==0)
                        F[i][j][l]+=F[i+1][p-1][l-1]*F[p+1][j][l];
                    if (code[s[i]]+code[s[p]]!=0&&code[s[i]]*code[s[p]]==0)
                        F[i][j][l]+=F[i+1][p-1][l-1]*F[p+1][j][l];
                }
            }
            if (s[i]==s[j]&&s[i]=='?')
                F[i][j][l]+=3*F[i+1][j-1][l-1];
            if (code[s[i]]>0&&code[s[i]]+code[s[j]]==0)
                F[i][j][l]+=F[i+1][j-1][l-1];
            if (code[s[i]]+code[s[j]]!=0&&code[s[i]]*code[s[j]]==0)
            {
                F[i][j][l]+=F[i+1][j-1][l-1];
            }
          //  P[i][j][l]=P[i][j][l-1]+F[i][j][l];
          //  cout<<i<<' '<<j<<' '<<l<<' '<<F[i][j][l]<<endl;
        }
   // cout<<F[2][3][0]<<endl;
    cout<<F[1][n][k]-F[1][n][k-1];
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("btn.inp","r",stdin);
    freopen("btn.out","w",stdout);
    solve();
}
