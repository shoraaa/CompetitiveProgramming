#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 55;
ll mask[N];
int n, m;
#define Size(x) __builtin_popcountll(x)
#define First(x) (__builtin_ffsll(x) - 1)

ll B = 0, A = 0, T = 0; int SZ = 0;
void call(ll R, ll P) {
  if (P == 0) {
    if (Size(R) > Size(B)) B = R;
    return;
  }
  if (Size(B) >= Size(P) + Size(R)) return;
  while (P > 0) {
    int i = First(P);
    call(R | (1LL << i), P & mask[i]);
    P ^= 1LL << i;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    mask[u] |= 1LL << v, mask[v] |= 1LL << u;

  call(0, (1LL << n) - 1); 
  SZ = Size(B) / 2;
  
  for (int i = 0, v; i < SZ; ++i) 
    v = First(B), B ^= 1LL << v, A |= 1LL << v;

  ll nA = 0, nB = 0;
  for (int i = 0; i < n; ++i) {
    if (B & (1LL << i) || (mask[i] & A) == A) {
      nB |= 1LL << i;
    } else {
      nA |= 1LL << i;
    }
  }
  int y = SZ; B = 0; call(0, nA);
  
  for (;;) {
    call(0, nA); int x = Size(B);
    if (x - y >= 2) {
      int i = First(A); nA ^= 1LL << i, nB |= 1LL << i; A ^= 1LL << i; 
      if (B & (1LL << i)) B ^= 1LL << i;
    } else if (x - y >= 1) {
      if (A ^ (A & B)) {
        int i = First(A ^ (A & B)); 
        nA ^= 1LL << i, nB |= 1LL << i; 
      } else {
        ll G = B ^ (A & B);
        while (G > 0) {
          int i = First(G); G ^= 1LL << i;
          if ((mask[i] & nB) != nB) {
            nA ^= 1LL << i, nB |= 1LL << i; B ^= 1LL << i; break;
          }
        }
      }
    } else break;
    y++;
  }

  cout << Size(nB) << '\n';
  while (nB > 0) {
    int i = First(nB); nB ^= 1LL << i;
    cout << i + 1 << ' ';
  }

  
	return 0;
}

