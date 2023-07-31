#include<bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define bit(s, i) (s & (1<<i))

using namespace std;

const int N = 1e6 + 5;
const int M = 1;
const int K = 1;
const int mod = 1e9+7;
const int inf = 2e9;
const long long Inf = 2e18;

typedef long long ll;
typedef pair < int, int > ii;

int mark[N];
void init() {
	for(int i=2;i*i<N;++i) 
	if(!mark[i]) for(int j=i*i;j<N;j+=i) mark[j] = i;
}

vector < int > vc;
void solve(int x) {
	while(mark[x]) {
		vc.pb(mark[x]);
		x /= mark[x];
	}
	if(x != 1) vc.pb(x);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    freopen("DIV.inp","r",stdin);
    freopen("DIV.out","w",stdout);

    init();

    int nTest, m;
    cin >> nTest;

    while(nTest --) {
    	cin >> m;
    	vc.clear();
    	for(int i=m;i<=m+2;++i) {
    		solve(i);
    		solve(i);
    	}
    	sort(vc.begin(), vc.end());
    	int cnt = 1;
    	long long res = 1;
    	for(int i=1;i<(int)vc.size();++i) {
    		if(vc[i] != vc[i - 1]) {
    			res *= (cnt + 1);
    			cnt = 1;
    		}
    		else cnt ++;
    	}
    	res *= (cnt + 1);
    	long long t = (res + 1) / 2;
    	
    	vc.clear();
    	for(int i=m;i<=m+2;++i) solve(i);
    	
    	sort(vc.begin(), vc.end());
    	cnt = 1;
    	res = 1;
    	for(int i=1;i<(int)vc.size();++i) {
    		if(vc[i] != vc[i - 1]) {
    			res *= (cnt + 1);
    			cnt = 1;
    		}
    		else cnt ++;
    	}
    	res *= (cnt + 1);
    	cout << t - res << endl;
    }
}