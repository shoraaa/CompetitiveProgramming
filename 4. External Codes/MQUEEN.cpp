#include <bits/stdc++.h>
using namespace std;
pair <int,int> a[12],b[12];
int n;
bool kt[12],tt[12];
int kc(int i,int j)
{
    return(max(abs(a[i].first-b[j].first),abs(a[i].second-b[j].second)));
}
int res=1e9,rr;
int getbit(int n,int i)
{
    return (n>>i)&1;
}
int f[12][100002];
int sumbit(int m)
{
    int p=0;
    for (int i=0;i<n;i++){
        p+=getbit(m,i);
    }
    return(p);
}
void getmax()
{
   for (int i=0;i<=n;i++){
        for (int j=0;j<(1<<n);j++) f[i][j]=1e9;
   }
   f[0][0]=0;
   for (int i=1;i<=n;i++){
        for (int j=1;j<(1<<n);j++){
            if (sumbit(j)!=i) continue;
            for (int t=0;t<n;t++){
                if (getbit(j,t)==1){
                    f[i][j]=min(f[i][j],f[i-1][j-(1<<t)]+kc(i,t+1));
                }
            }
           // cout<<i<<' '<<j<<' '<<f[i][j]<<'\n';
        }
   }
   res=min(res,f[n][(1<<n)-1]);
}
bool check(int i)
{
   // if (i==1) return(true);
    for (int j=1;j<i;j++){
        if (b[j].second==b[i].second) return(false);
        if  (abs(b[i].first-b[j].first)==abs(b[i].second-b[j].second)) return(false);
    }
    return(true);
}
void tryy(int i)
{
    for (int j=1;j<=n;j++) if (tt[j]==false){
        tt[j]=true;
        b[i]={i,j};
        if (check(i)){
            if (i==n) {
               // memset(kt,false,sizeof kt);
               // rr=0;
                getmax();
                //cout<<rr<<endl;
            }
            else tryy(i+1);
        }
        tt[j]=false;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("MQUEEN.inp","r",stdin);
    freopen("MQUEEN.out","w",stdout);
    cin>>n;
    char x;
    int y;
    for (int i=1;i<=n;i++){
        cin>>x>>y;
        a[i]={x-'a'+1,y};
        //cout<<a[i].first<<' '<<a[i].second<<endl;
    }
    tryy(1);
    if (n<=3 && n!=1) cout<<-1;
    else cout<<res;

}
