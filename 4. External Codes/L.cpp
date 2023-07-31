#include<bits/stdc++.h>
#define pi pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5;

string s;
int k;
int d[N], a[N];

void solve(){
    cin >> s >> k;

    if ( k == 1 ) { cout << "OH NO!\n"; return; }

    for (int i = 0; i <= 25; i ++) d[i] = 0;
    for (int i = 0; i < s.size(); i ++)
        d[s[i]-'a'] ++;

    priority_queue<pi> heap;
    for (int i = 0; i <= 25; i ++) if ( d[i] ){
        int tmp;
        if ( d[i] % (k-1) == 0 ) tmp = d[i]/(k-1);
        else tmp = (d[i]+k-1)/(k-1) ;

        heap.push({tmp, i});
    }

    int cur = 1;
    while ( heap.size() ){
        int c = heap.top().se, dc = heap.top().fi;
        heap.pop();

        for (int i = cur; i <= cur + 2 * dc - 1; i += 2) a[i] = c;

        int rem = dc-1, id = cur+1;

        while ( heap.size() && rem ){
            int tc = heap.top().se, tdc = heap.top().fi;
            heap.pop();

            if ( tdc > rem ){
                tdc -= rem;
                for (int i = 1; i <= rem; i ++){
                    a[id] = tc, id += 2;
                }
                rem = 0;
                heap.push({tdc, tc});
            }
            else{
                rem -= tdc;
                for (int i = 1; i <= tdc; i ++){
                    a[id] = tc, id += 2;
                }
            }
        }

        if ( rem ) { cout << "OH NO!\n"; return; }

        cur += 2*dc - 1;
    }

    for (int i = 1; i < cur; i ++){
        for (int j = 1; j <= min(k-1, d[a[i]]); j ++)
            cout << (char)(a[i]+'a');
        d[a[i]] -= k-1;
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    if ( fopen("L.inp", "r") ){
        freopen("L.inp", "r", stdin);
        freopen("L.out", "w", stdout);
    }

    int test;
    cin >> test;
    while ( test -- )
        solve();

    return 0;
}
