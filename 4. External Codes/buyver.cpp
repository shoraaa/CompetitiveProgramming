#include<bits/stdc++.h>

#define bit(s, i) (s & (1<<i))
#define fi first
#define se second
#define pb push_back
#define endl '\n'
#define int long long
using namespace std;

const int N = 1005;
const int M = 1;
const int K = 1;
const int inf = 2e9;
const long long Inf = 2e18;
const int mod = 1e9 + 7;

typedef pair < int, int > ii;
typedef long long ll;

int n, m, a[N], vis[N], siz[N], res[N][N], par[N];
vector < int > adj[N];

void mini(long long &a, long long b) {
	if(a > b) a = b;
}

long long dp[N][N][3], pd[N][N][3], Dp[N][N];
void dfs(int u, int p) {
	vis[u] = 1;
	for(int v : adj[u]) if(v != p) dfs(v, u);

	siz[u] = 1;
	dp[u][0][0] = 0, dp[u][1][2] = a[u];
	// for(int i=0;i<=siz[u];++i) {
	// 	if(u == 1) cerr << i << ' ' << dp[u][i][0] << ' ' << dp[u][i][1] << ' ' << dp[u][i][2] << endl;
	// }
	cerr << endl;
	for(int v : adj[u]) if(v != p) {
		//if(u == 1) cerr << v << ":" << endl;
		for(int i=siz[u];i>=0;--i)
		for(int j=siz[v];j>=0;--j) {
			// if(u == 1) cerr << j << ' ' << dp[v][j][0] << ' ' << dp[v][j][1] << endl;
			pd[u][i][0] = dp[u][i][0], pd[u][i][1] = dp[u][i][1], pd[u][i][2] = dp[u][i][2]; 
			mini(dp[u][i + j][0], pd[u][i][0] + min(dp[v][j][0], dp[v][j][1]));
			mini(dp[u][i + j][2], pd[u][i][2] + dp[v][j][0]);
			mini(dp[u][i + j + 1][1], pd[u][i][0] + a[u] + min(dp[v][j][1], dp[v][j][2]));
			mini(dp[u][i + j][1], pd[u][i][1] + min({dp[v][j][0], dp[v][j][1], dp[v][j][2]}));
		}
		
		siz[u] += siz[v];
		// for(int i=0;i<=siz[u];++i) {
		// 	if(u == 1) cerr << i << ' ' << dp[u][i][0] << ' ' << dp[u][i][1] << ' ' << dp[u][i][2] << endl;
		// }
		// cerr << endl;
	}

	//cerr << u << " :" << endl;
	//for(int i=0;i<=siz[u];++i) cerr << i << ' ' << dp[u][i][0] << ' ' << dp[u][i][1] << ' ' << dp[u][i][2] << endl;
}

signed main() {
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	// freopen("buyver.in", "r", stdin);
	// freopen("buyver.out", "w", stdout);

	cin >> n >> m;
	for(int i=1;i<=n;++i) cin >> a[i];

	for(int i=1, u, v;i<=m;++i) {
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	memset(dp, 0x3f, sizeof dp);
	int cnt = 0;
	for(int i=1;i<=n;++i) if(!vis[i]) {
		dfs(i, 0);
		cnt ++;
		par[cnt] = i;
		for(int j=0;j<=siz[i];++j) {
			res[cnt][j] = min(dp[i][j][0], dp[i][j][1]);
		}
	}

	int all = 0;
	memset(Dp, 0x3f, sizeof Dp);
	Dp[0][0] = 0;
	for(int i=0;i<cnt;++i) {
		for(int j=0;j<=all;++j)
		for(int p=0;p<=siz[par[i + 1]];++p) mini(Dp[i + 1][j + p], Dp[i][j] + res[i + 1][p]);
		all += siz[par[i + 1]];
	}

	for(int i=n-1;i>=0;--i) Dp[cnt][i] = min(Dp[cnt][i], Dp[cnt][i + 1]);

	int Q; cin >> Q;
	while(Q --) {
		int x;
		cin >> x;
		int l = 0, r = n, mid, ans;
		while(l <= r) {
			mid = (l + r) >> 1;
			if(Dp[cnt][mid] <= x) {
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		cout << ans << endl;
	}
}	
