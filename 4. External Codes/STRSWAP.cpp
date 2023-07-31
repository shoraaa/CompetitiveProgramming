#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define II pair < int , int > 
#define pb push_back
#define mset(a , b) memset(a , b , sizeof a);
#define Hmax priority_queue < int > 
#define Hmin priority_queue < int , vector < int > , greater < int > >
#define IImax priority_queue < II >  
#define IImin priority_queue < II , vector < II > , greater < II > >
#define FOR(i , a , b) for(int i = a ; i <= b ; ++i)
#define FOD(i , a , b) for(int i = a ; i >= b ; --i)
const int inf = 1e9;
const int N = 2e6 + 3;
string st;
int n , a[N] , s[N][4] , num[4][4] , val[4];
void Input()
{
    cin >> st;
    n = st.size();
    for(int i = 1 ; i <= n ; ++i)
    {
    	a[i] = st[i - 1] - 'A' + 1;
    	a[i + n] = a[i];
    }
}
void Prepare()
{
	for(int i = 1 ; i <= 2 * n ; ++i)
	{
		for(int j = 1 ; j <= 3 ; ++j) s[i][j] = s[i - 1][j];
		s[i][a[i]]++;
	}
}
int Cal(int low , int high , int v2 , int v3)
{
	num[1][2] = s[low + val[1] - 1][2] - s[low - 1][2];
	num[1][3] = s[low + val[1] - 1][3] - s[low - 1][3];
	num[v2][1] = s[low + val[1] + val[v2] - 1][1] - s[low + val[1] - 1][1];
	num[v2][v3] = s[low + val[1] + val[v2] - 1][v3] - s[low + val[1] - 1][v3];
	num[v3][1] = s[high][1] - s[low + val[1] + val[v2] - 1][1];
	num[v3][v2] = s[high][v2] - s[low + val[1] + val[v2] - 1][v2];

	int Res = 0 , Tem;
	Tem = min(num[1][v2] , num[v2][1]);
	Res += Tem;
	num[1][v2] -= Tem , num[v2][1] -= Tem;
	Tem = min(num[1][v3] , num[v3][1]);
	Res += Tem;
	num[1][v3] -= Tem , num[v3][1] -= Tem;
	Tem = min(num[v2][v3] , num[v3][v2]);
	Res += Tem;
	num[v2][v3] -= Tem , num[v3][v2] -= Tem;
	Res = Res + 2 * (num[1][2] + num[1][3]);
	return Res;
}
void Solve()
{
	Prepare();
	int Res = inf;
	for(int i = 1 ; i <= 3 ; ++i) val[i] = s[n][i];
    for(int i = 1 ; i <= n ; ++i)
    {
    	Res = min({Res , Cal(i , i + n - 1 , 2 , 3) , Cal(i , i + n - 1 , 3 , 2)});
    }
    cout << Res;
}
#undef int
int main()
{
    if(fopen("trash.inp" , "r"))
        freopen("trash.inp" , "r" , stdin) , freopen("trash.out" , "w" , stdout);
    else freopen("STRSWAP.inp" , "r" , stdin) , freopen("STRSWAP.out" , "w" , stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solve();
}