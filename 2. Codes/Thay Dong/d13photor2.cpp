#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
int a[N][N];
int n, m;


void negat(string& s) {
  if (s[0] == '-') return s = string(1, s[1]), void();
  return s = '-' + s, void();
}

string i = "i", j = "j";

void fA() {
  negat(i);
  swap(i, j);
}

void fX() {
  negat(j);
  swap(i, j);
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1;i <= n; ++i) {
    for (int j = 1;j <= m; ++j) {
      cin >> a[i][j]; 
    }
  }
  
  string s;
  cin >> s;
  
  for (char c : s) {
    switch (c) {
      case '1':
        swap(i, j);
        break;
      case '2':
        negat(i); negat(j);
        swap(i, j);
        break;
      case 'H':
        negat(i); 
        break;
      case 'V':
        negat(j);
        break;
      case 'A':
        fA();
        break;
      case 'B':
        fA(); fA();
        break;
      case 'C':
        fA(); fA(); fA();
        break;
      case 'X':
        fX();
        break;
      case 'Y':
        fX(); fX();
        break;
      case 'Z':
        fX(); fX(); fX();
        break;
      default:
        assert(0);
    }
  }
  
  vector<tuple<int, int, int>> pos, nxtPos;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      pos.emplace_back(i, j, a[i][j]);
    }
  }
  for (auto& p : pos) {
    int x, y, z; tie(x, y, z) = p;
  if (i == "i" && j == "j") {
    nxtPos.emplace_back(x, y, z);
  } else if (i == "j" && j == "i") {
    nxtPos.emplace_back(y, x, z);
  } else if (i == "-j" && j == "-i") {
    nxtPos.emplace_back(m-y+1, n-x+1, z);
  }else if (i == "-i" && j == "j") {
    nxtPos.emplace_back(n-x+1, y, z);
  }else if (i == "i" && j == "-j") {
    nxtPos.emplace_back(x, m-y+1, z);
  }else if (i == "j" && j == "-i") {
    nxtPos.emplace_back(y, n-x+1, z);
  }else if (i == "-i" && j == "-j") {
    nxtPos.emplace_back(n-x+1, m-y+1, z);
  }else if (i == "-j" && j == "i") {
    nxtPos.emplace_back(m-y+1, x, z);
  } else assert(0);
  }
  
  sort(pos.begin(), pos.end());
  sort(nxtPos.begin(), nxtPos.end());
  
  cout << (pos != nxtPos);
  
	return 0;
}

