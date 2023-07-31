#include <bits/stdc++.h>
using namespace std;
long long n;
int base;
int m,k;
long long F[3002][3002];
typedef pair <pair <int,int>,long long> pii;
pii d[] = {{{2,1},1},{{3,1},4},{{4,1},14},{{5,1},51},{{6,1},202},{{7,1},876},{{8,1},4139},{{9,1},21146},{{10,1},115974},{{11,1},678569},{{1,2},1},{{2,2},8},{{3,2},65},{{4,2},711},{{5,2},10456},{{6,2},198090},{{7,2},4659137},{{1,3},2},{{2,3},30},{{3,3},685},{{4,3},27035},{{5,3},1688359},{{1,4},4},{{2,4},108},{{3,4},6720},{{4,4},911837},{{1,5},6},{{2,5},338},{{3,5},58615},{{4,5},26908755},{{1,6},10},{{2,6},1042},{{3,6},476780},{{1,7},14},{{2,7},2997},{{3,7},3608347},{{1,8},21},{{2,8},8405},{{3,8},25781988},{{1,9},29},{{2,9},22651},{{1,10},41},{{2,10},59520},{{1,11},55},{{2,11},151957},{{1,12},76},{{2,12},379692},{{1,13},100},{{2,13},927621},{{1,14},134},{{2,14},2224234},{{1,15},175},{{2,15},5236585},{{1,16},230},{{1,17},296},{{1,18},384},{{1,19},489},{{1,20},626},{{1,21},791},{{1,22},1001},{{1,23},1254},{{1,24},1574},{{1,25},1957},{{1,26},2435},{{1,27},3009},{{1,28},3717},{{1,29},4564},{{1,30},5603},{{1,31},6841},{{1,32},8348},{{1,33},10142},{{1,34},12309},{{1,35},14882},{{1,36},17976},{{1,37},21636},{{1,38},26014},{{1,39},31184},{{1,40},37337}};
int res[50][50];
int check(int a,int b)
{
    vector <int> P,Q;
    while (a>0)
    {
        P.push_back(a%base);
        a/=base;
    }
    while (P.size()<m) P.push_back(0);
    while (b>0)
    {
        Q.push_back(b%base);
        b/=base;
    }
    while (Q.size()<m) Q.push_back(0);
    for (int i=0;i<m;i++)
        if (P[i]<Q[i]) return 0;
    return 1;
}
int tru(int a,int b)
{
    vector <int> P,Q;
    while (a>0)
    {
        P.push_back(a%base);
        a/=base;
    }
    while (P.size()<m) P.push_back(0);
    while (b>0)
    {
        Q.push_back(b%base);
        b/=base;
    }
    while (Q.size()<m) Q.push_back(0);
    for (int i=0;i<m;i++)
        P[i]-=Q[i];
    int ans=0;
    for (int i=m-1;i>=0;i--)
        ans=ans*base+P[i];
    return ans;
}

void setup()
{
    for (int i=0;i<78;i++)
        res[d[i].first.first][d[i].first.second]=d[i].second;
}
void solve()
{
    cin>>n;
    m=0;k=0;
    for (int i=2;i<=trunc(sqrt(n));i++)
        if (n%i==0)
    {
        m++;
        int dem=0;
        while (n%i==0)
        {
            dem++;
            n/=i;
        }
        if (k==0) k=dem;
    }
    if (n>1) m++;
    cout<<res[m][k]<<'\n';
    /*if (res[m][k]>0) {cout<<res[m][k]-1<<'\n';return;}
   //cout<<m<<' '<<k<<endl;
    base=k+1;
    memset(F,0,sizeof(F));
    int vmax=0;
    for (int i=1;i<=m;i++)
        vmax=vmax*base+k;
    for (int i=0;i<=vmax;i++)
        F[0][i]=1;
    for (int i=1;i<=vmax;i++)
        for (int j=1;j<=vmax;j++)
        {
            F[i][j]=F[i][j-1];
            if (check(i,j)) F[i][j]+=F[tru(i,j)][j];
        }
    res[m][k]=F[vmax][vmax];
    cout<<F[vmax][vmax]-1<<'\n';*/
}
int main()
{
    freopen("factor.inp","r",stdin);
    freopen("factor.out","w",stdout);
    setup();
    int t;cin>>t;
    while (t--) solve();
}
