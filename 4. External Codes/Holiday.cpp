#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5,mod=1e9+7,inf=0x3f3f3f3f;
#define X first
#define Y second
#define pb push_back
using ll=long long;
typedef pair < int , int > ii;
typedef pair < long long , int > II;
int now;
ll IT[MAX*4];
int ST[MAX*4];
int a[MAX];
ii b[MAX];
ll dp[2][MAX*2+MAX/2],pd[2][MAX*2+MAX/2];
void upd(int x,int id,int l,int r){
    if(x<l || x>r) return;
    if(l==r) {
        ST[id]++;
        IT[id]=b[l].X;return;
    }
    int mid=l+r>>1;
    upd(x,id<<1,l,mid);
    upd(x,id*2+1,mid+1,r);
    ST[id]=ST[id<<1]+ST[id*2+1];
    IT[id]=IT[id<<1]+IT[id*2+1];
}
ll get(int x,int id,int l, int r){
    if(x==0) return 0;
    int mid=l+r>>1;
    if(ST[id<<1]<=x) return IT[id<<1]+get(x-ST[id<<1],id*2+1,mid+1,r);
    else return get(x,id*2,l,mid);
}
int d;
void solve(int n,bool tt){
    vector < ii > Q[2];
    Q[0].pb(ii(n,d+1));
    int x=0,y=1;
    while(Q[x].size()<=d){
        memset(ST,0,sizeof ST);
        memset(IT,0,sizeof IT);
        int po=0,pre=0;
        int ma=0;
        for(ii u: Q[x]){
            II ans={0,0};
            int mi=u.Y+pre>>1;

            if(mi!=pre) {
                if(mi>=2*po) ans=max( ans,II(IT[1],-po) );
                else ans=max(ans,II( get(mi-po,1,1,n),-po) );
                ma=min(u.X,mi-1);
                for(int i=po+1;i<=ma;i++){
                    upd(a[i],1,1,n);
                    if(mi>=2*i) ans=max( ans,II(IT[1],-i) );
                    else ans=max(ans,II( get(mi-i,1,1,n),-i) );
                }
                dp[tt][mi]=ans.X;
                Q[y].pb(ii(-ans.Y,mi));
            }
            else{
                ma=min(u.X,mi-1);
                for(int i=po+1;i<=ma;i++)
                    upd(a[i],1,1,n);
            }
            Q[y].pb(u);
            po=ma;pre=u.Y;
        }
        Q[x].clear();
        x^=1;y^=1;
    }
    Q[x].clear();
    Q[0].pb(ii(n,d+1));
    x=0;y=1;

    while(Q[x].size()<=d){
        memset(ST,0,sizeof ST);
        memset(IT,0,sizeof IT);
        int po=0,pre=0;
        int ma=0;
        for(ii u: Q[x]){
            II ans={0,0};
            int mi=u.Y+pre>>1;
            if(mi>=3*po) ans=max( ans,II(IT[1],-po) );
            else ans=max(ans,II( get(mi-po*2,1,1,n),-po) );
            ma=min(u.X,mi/2);
            for(int i=po+1;i<=ma;i++){
                upd(a[i],1,1,n);
                if(mi>=3*i) ans=max( ans,II(IT[1],-i) );
                else ans=max(ans,II( get(mi-i*2,1,1,n),-i) );
            }
            if(mi!=pre) {
                pd[tt][mi]=ans.X;
                Q[y].pb(ii(-ans.Y,mi));
            }
            Q[y].pb(u);
            po=ma;pre=u.Y;
        }
        Q[x].clear();
        x^=1;y^=1;
    }
    //for(int i=1;i<=n;i++) cout<<b[a[i]].X<<'\n'; for(int i=1;i<=d;i++) cout<<i<<' '<<dp[tt][i]<<' '<<pd[tt][i]<<'\n';cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    freopen("Holiday.inp","r",stdin);
    freopen("Holiday.out","w",stdout);
    int m,n,PLUS;
    cin>>m>>n>>d;
    n++;
    for(int i=1;i<n;i++){
        cin>>a[n-i];
        b[i]=ii(a[n-i],n-i);
    }
    m-=n;
    n--;
    sort(b+1,b+1+n,greater < ii >() );
    for(int i=1;i<=n;i++)
        a[b[i].Y]=i;
    solve(n,0);
    cin>>PLUS;
    for(int i=1;i<=m;i++){cin>>a[i];b[i]=ii(a[i],i);}
    sort(b+1,b+1+m,greater < ii >() );
    for(int i=1;i<=m;i++)
        a[b[i].Y]=i;
    solve(m,1);
    ll ans=0;
    for(int i=1;i<=d;i++){
        ans=max({ans,dp[1][i]+pd[0][d-i],dp[0][i]+pd[1][d-i],dp[1][i-1]+PLUS+pd[0][d-i],dp[0][i-1]+PLUS+pd[1][d-i]});
    }
    cout<<ans;
}
