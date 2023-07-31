                 /*..... .
                 .';:;;;;'':.
                .:::::::::cl'
                .c;;o,.cc::::.
                ';l:.. ..;;;;.
                 .,::.'',:...
                  '.'cxdo;..d.
                  d..:olo.'dO.
                  kk. .. :kOO.
                 .k0k...'000d.
                  c00'.,00k:..
                  l00..xOk;..co'
                 .l00cdOO, ...oO;.
           .,;;. .:ld::do  .  .OOx'.
       ,cokcc,......;. ..      oOO00Oooc'
    .oOOOc..... .......      ..oK000OOOOOl.
   :OOOO:....    .'...      .lO0KK000OOOOOOo.
   ,OOO00;  ..   .           x0KK0000OOOOOOO:.
    'ck00k.  ...  ...... ... ':000OOOOOOOOOk;.
      :OOO0kdld:':O0:.,,,l'.':'OOOOOOo:l:;'.
       .;ooolOOOOOO000O00000OOOOOOx:..
             .''....;coolc,'',;.*/
#include <bits/stdc++.h>
#define print(_v) for (auto &_ : _v) {cerr << _ << ' ';} cerr << endl;
using namespace std;
void file() {
  const string FILE_NAME = "conference";
  freopen((FILE_NAME + ".in").c_str(), "r", stdin);
  freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
using ll = long long;
const int oo = 1e9;
const int N = 1e6 + 1;
int n, m, k;
int x[N], y[N], ne[N], tim[N], ans[N], t[N], met[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  file();
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++)
    cin >> x[i] >> y[i];
  memset(t, 0x3f, sizeof(t));
  for (int i = m; i; --i) {
    int u = x[i], v = y[i];
    if (u > k && v > k) continue;
    if (u > k) 
      ne[u] = u, t[u] = i;
    if (v > k) 
      ne[v] = v, t[v] = i;
    if (u <= k) {
      if (ne[v]) {
        if (t[u] > t[v]) 
           ne[u] = ne[v], t[u] = t[v];
        if (!ans[u]) 
           tim[u] = i, ans[u] = ne[v];
      }
    }
    swap(u, v);
    if (u <= k) {
      if (ne[v]) {
        if (t[u] > t[v]) 
           ne[u] = ne[v], t[u] = t[v];
        if (!ans[u]) 
           tim[u] = i, ans[u] = ne[v];
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    int u = x[i], v = y[i];
    if (u <= k && tim[u] == i)
      met[u] = 1;
    if (v <= k && tim[v] == i)
      met[v] = 1;
      if (met[u]) met[v] = 1;
      if (met[v]) met[u] = 1;
    }
  for (int i = 1; i <= k; i++)
    if (!ans[i]) cout << "-1 ";
    else cout << tim[i] << ' ';
  cout << '\n';
  int t = 0;
  for (int i = k + 1; i <= n; i++)
    t += met[i];
  cout << t << ' ';
  for (int i = k + 1; i <= n; i++)
    if (met[i]) cout << i << ' ';
  cout << '\n';
  for (int i = 1; i <= k; i++)
    if (!ans[i]) cout << "-1 ";
    else cout << ans[i] << ' ';
}

