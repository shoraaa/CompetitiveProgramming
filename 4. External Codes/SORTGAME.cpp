#include <bits/stdc++.h>
using namespace std;
int a[200];
int n;
void solve(int u,int v)
{
    for (int i=v-1;i>=u+1;i--){
        swap(a[i],a[i+1]);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("SORTGAME.inp","r",stdin);
    freopen("SORTGAME.out","w",stdout);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    int i=1;
    int res=0;
    while (i<n){
        for (int j=i+1;j<=n;j++){
            if (a[j]==a[i]){
                res+=j-i-1;
                solve(i,j);
                i++;
                break;
            }
        }
        i++;
    }
    cout<<res;
}
