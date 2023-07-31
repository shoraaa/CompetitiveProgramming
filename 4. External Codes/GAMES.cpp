
#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define pb push_back
#define int long long
using ii = pair < int , int > ;
const int MAX = 1e5,N=1e6+5;
int a[6];
struct qb{
    int x,y,z;
    qb(){}
    qb(int a,int b,int c){
        x=a,y=b,z=c;
    }
    void out(){
        cout<<x<<' '<<y<<' '<<z<<'\n';
    }
};
signed main() {
    freopen("GAMES.inp", "r", stdin);
    freopen("GAMES.out", "w", stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //memset(mark,1,sizeof mark);
    vector < qb > ans;
    for(int i=1;i<=5;i++) cin>>a[i];
    a[0]=MAX;
    for(int i=2;i<=5;i++){
        int cs=0;

        for(int j=1;j<=5;j++)if(a[j]<a[cs] && a[j]) cs=j;
        if(!cs) break;
        int u=0,v=0;
        int m=a[cs];a[cs]=0;
        for(int j=1;j<cs;j++)if(a[j]){
            if(u) v=j;
            else u=j;
        }
        for(int j=5;j>cs;j--)if(a[j]){
            if(u) v=j;
            else u=j;
        }
        if(!u || !v) {a[cs]=m;break;}
        a[u]-=m;a[v]+=m*2;
            //cout<<cs<<' '<<u<<' '<<v<<'\n';
        for(int j=0;j<m;j++) ans.pb(qb(cs,u,v));
    }
    int cn=0;
    for(int i=1;i<=5;i++) {cn+=(a[i]!=0);}//cout<<a[i]<<'\n';

    if(cn==2){
            int u=0,v=0;
        for(int i=1;i<=5;i++)if(a[i]){
            if(u) v=i;
            else u=i;
        }
        if(a[u]==a[v]){
            int z=1;
            while(a[z]) z++;
            int m=a[u];
            for(int i=0;i<m;i++){
                ans.pb(qb(u,v,z));
                a[u]--;a[v]--;a[z]+=2;
            }
        }else {
            int z=1;
            while(a[z]) z++;
            ans.pb(qb(u,v,z));
            a[u]--;a[v]--;a[z]+=2;
            if(!a[u]){
                ans.pb(qb(z,v,u));
                a[z]--;a[v]--;a[u]+=2;
            }
            if(!a[v]){
                ans.pb(qb(z,u,v));
                a[z]--;a[u]--;a[v]+=2;
            }
            cn=0;for(int i=1;i<=5;i++) {cn+=(a[i]!=0);}
        }
    }
    bool more=0;


    if(cn==3){
        int u=0,v=0,k=0;
        for(int i=1;i<=5;i++)if(a[i]){
            if(u)
            {
                if(v) k=i;
                else v=i;
            }
            else u=i;
        }

        if(a[u]%3==a[k]%3) swap(k,v);
        if(a[v]%3==a[k]%3) swap(k,u);
        if(a[u]%3==a[v]%3){

            //cout<<a[u]<<' '<<a[v]<<' '<<a[k]<<'\n';
            if(a[u]<a[v]) swap(u,v);
            while(a[u]!=a[v]){
                if(a[k]) {
                    a[u]--;a[k]--;a[v]+=2;
                    ans.pb(qb(u,k,v));
                }
                else{
                    if(!a[u]) break;
                    a[u]--;a[v]--;a[k]+=2;
                    ans.pb(qb(u,v,k));
                    a[u]--;a[k]--;a[v]+=2;
                    ans.pb(qb(u,k,v));
                }
            }
            if(a[u]==a[v]){
                int m=a[v];
                for(int i=0;i<m;i++){
                    ans.pb(qb(u,v,k));
                    a[u]--;a[v]--;a[k]+=2;
                }
            }

            //if(!a[u] && !a[k]) break;
        }
        else{

            if(a[v]%3==0) swap(u,v);
            if(a[k]%3==0) swap(u,k);
            if(a[k]%3==1) swap(v,k);
            int z=1;
            while(a[z]) z++;
            ans.pb(qb(u,v,z));
            /// u v k z
            /// 0 1 2 0
            a[v]--;a[u]--;a[z]+=2;
            /// 2 0 2 2
            while(a[v]!=0){
                if(a[u]>2)
                    for(int i=0;i<3;i++){ans.pb(qb(u,v,z));a[v]--;a[u]--;a[z]+=2;}
                else{
                    if(a[k]>2)
                    for(int i=0;i<3;i++){ans.pb(qb(k,v,u));a[v]--;a[k]--;a[u]+=2;}
                    else
                    if(a[z]>2)
                    for(int i=0;i<3;i++){ans.pb(qb(z,v,u));a[v]--;a[z]--;a[u]+=2;}
                }

            }
            if(1){
                v=z;
                if(a[u]<a[v]) swap(u,v);
                while(a[u]!=a[v]){
                    if(a[k]) {
                        a[u]--;a[k]--;a[v]+=2;
                        ans.pb(qb(u,k,v));
                    }
                    else{
                        if(!a[u]) break;
                        a[u]--;a[v]--;a[k]+=2;
                        ans.pb(qb(u,v,k));
                        a[u]--;a[k]--;a[v]+=2;
                        ans.pb(qb(u,k,v));
                    }
                }
                if(a[u]==a[v]){
                    int m=a[v];
                    for(int i=0;i<m;i++){
                        ans.pb(qb(u,v,k));
                        a[u]--;a[v]--;a[k]+=2;
                    }
                }
            }
        }
    }

    cout<<ans.size()<<'\n';
    for(qb u:ans) u.out();
    //for(int i=1;i<=5;i++) cout<<a[i]<<' ';
}
