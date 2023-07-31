#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX=1005,mod=1e9+7,inf=0x3f3f3f3f;
using ii = pair < ll , ll > ;
int f[MAX][MAX][2],F[MAX][MAX][2],cnt[MAX];
#define X first
#define Y second
#define pb push_back
//vector < int > pr[MAX];
int n,m;
//ll a[MAX];
int A,B;
int get(int a,int b){
    a+=b;if(a>=mod) a-=mod;return a;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen(".inp","r",stdin);freopen(".out","w",stdout);
    int T;cin>>T;
    while(T--){
        memset(F,0,sizeof F);memset(f,0,sizeof f);memset(cnt,0,sizeof cnt);
        cin>>n;
        cin>>A>>B;
        //cout<<mod*2;
        if(A>B) swap(A,B);
        ll ans=1;
        f[0][0][1]=1;
        f[0][0][0]=1;
        cnt[0]=1;
        F[0][0][0]=1;
        F[0][0][1]=1;
        for(int i=1;i<=n;i++){ans=ans<<1;if(ans>=mod) ans-=mod;}
        for(int i=1;i<=n;i++){
            if(i>=A) f[i][0][0]=(cnt[i-1]-cnt[i-A]+mod)%mod;
            else f[i][0][0]=cnt[i-1];
            F[i][i][0]=get( F[i-1][i][0],f[i][0][0] );
            for(int j=1,ma=min(B-1,i);j<=ma;j++){
                if(i>=A) f[i][j][0]=F[i-A][i-j][1];
                F[i][i-j][0]=get( F[i-1][i-j][0],f[i][j][0] );
            }
            for(int j=1,ma=min(B-1,i);j<=ma;j++){
                f[i][j][1]=F[i-1][i-j][0];
                F[i][i-j][1]=get(F[i-1][i-j][1],f[i][j][1]);
                cnt[i]=get(f[i][j][1],cnt[i]);
            }
            cnt[i]=get(cnt[i-1],cnt[i]);
        }
        ll temp=0;
        for(int j=0;j<B;j++){
            temp=(temp+f[n][j][1]+f[n][j][0])%mod;
        }
        cout<<(ans-temp+mod)%mod<<'\n';
    }

}
