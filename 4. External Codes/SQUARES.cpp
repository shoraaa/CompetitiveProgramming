#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ii pair<int,int>
#define iii pair<int,ii>
#define fi first
#define se second 
#define pb push_back
#define trash trash
const int oo=1e9;
const int Mod=1e9+7;
const long long OO=1e18;
const int N=300+5;
int n, m, k, a[N][N];
bitset<N>d[N][N], l[N][N], r[N][N], up[N][N], len[N];
void sub3()
{
	int ans = 0;
	for(int i=1; i<min(n,m); i++) ans += (n-i)*(m-i)*i;
	cout<<ans;
}
void sub4()
{
	int cnt=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)a[i][j] = a[i][j]==-1 ? 0 : 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1 ; j <= m; j++)
		{
			up[i][j] = up[i][j-1]<<1;
			l[i][j] = l[i-1][j]<<1;
			if(a[i][j])
			{
				up[i][j][0]=1;
				l[i][j][0]=1;
			}
		}
	for(int i=n; i>=1; i--)
		for(int j=m; j>=1; j--)
		{
			d[i][j] = d[i][j+1]<<1;
			r[i][j] = r[i+1][j]<<1;
			if(a[i][j])d[i][j][0] = r[i][j][0] = 1;
		}
	for(int i=1; i<=min(n,m); i++)
	{
		len[i] = len[i-1]<<1;
		len[i][0]=1;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			for(int h = 1; h <= min(n-i,m-j); h++)
			{
				cnt += (up[i+h][j+h] & r[i][j+h] & d[i][j] & l[i+h][j] & len[h]).count();
			}
	cout<<cnt;
}
void in()
{
	cin >> n >> m >> k;
	if(!k)sub3();
	else
	{
		for(int i=1; i<=k; i++)
		{
			int u, v; cin >> u >> v; a[u][v]=-1;
		}
		sub4();
	}
}
void solve()
{
	
}
void file()
{
	if(fopen("trash.inp", "r"))
    	freopen("trash.inp", "r", stdin), freopen("trash.out", "w", stdout);
 	 else freopen("squares.inp", "r", stdin), freopen("squares.out", "w", stdout);
}
int main()
{
  file();
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  in();
  solve();
}