#include <bits/stdc++.h>
using namespace std;

struct info{
    int x, p, d, t;

    info(){}

    info(int x, int p, int d, int t):
    x(x), p(p), d(d), t(t){}

    bool operator < (const info &o)
    const {return d > o.d;}
};

const int N = 5e4 + 5;
const int K = 505;
priority_queue <info> pq;
int dis[N][K], di[N];
vector <int> has[N];
int b[N], p[N];

int main(){
    freopen("sky.inp", "r", stdin);
    freopen("sky.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int m, n; cin >> m >> n;
    for (int i = 0; i < n; i++){
        cin >> b[i] >> p[i];
        has[b[i]].push_back(i);
    }
    memset(dis, 0x3f, sizeof dis);
    memset(di, 0x3f, sizeof di);
    if (p[0] <= K){
        dis[b[0]][p[0]] = 0;
        pq.emplace(b[0], p[0], 0, 0);
    }
    else {
        di[b[0]] = 0;
        for (int i : has[b[0]])
            pq.emplace(b[i], p[i], 0, 0);
    }
    while (!pq.empty()){
        auto u = pq.top(); pq.pop();
        if (u.p <= K){
            if (dis[u.x][u.p] < u.d) continue;
        }
        else {
            if (di[u.x] < u.d) continue;
        }
        if (u.x == b[1]){
            cout << u.d << '\n'; return 0;
        }
        if (!u.t){
            if (di[u.x] > u.d){
                pq.emplace(u.x, u.p, u.d, 1);
                di[u.x] = u.d;
            }
            if (u.p <= K){
                if (u.x + u.p <= m &&
                dis[u.x + u.p][u.p] > u.d + 1){
                    dis[u.x + u.p][u.p] = u.d + 1;
                    pq.emplace(u.x + u.p, u.p, u.d + 1, 0);
                }
                if (u.x - u.p >= 0 &&
                dis[u.x - u.p][u.p] > u.d + 1){
                    dis[u.x - u.p][u.p] = u.d + 1;
                    pq.emplace(u.x - u.p, u.p, u.d + 1, 0);
                }
            }
            else {
                for (int i = 1; u.x + i * u.p <= m; i++){
                    int nx = u.x + i * u.p;
                    if (di[nx] > u.d + i){
                        di[nx] = u.d + i;
                        pq.emplace(nx, u.p, u.d + i, 1);
                    }
                }
                for (int i = 1; u.x - i * u.p >= 0; i++){
                    int nx = u.x - i * u.p;
                    if (di[nx] > u.d + i){
                        di[nx] = u.d + i;
                        pq.emplace(nx, u.p, u.d + i, 1);
                    }
                }
            }
        }
        else {
            for (int i : has[u.x])
                pq.emplace(b[i], p[i], u.d, 0);
        }
    }
    cout << "-1\n"; return 0;
}