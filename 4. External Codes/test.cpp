#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 21, M = 1e5 + 3;
const int INF = 1e9 + 5;
int a[N][M], val[M];
int max_without_h1[M], max_without_h2[M];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  
  ll res = 0;
  val[0] = INF;
  
  
  for (int h1 = 1; h1 <= n; ++h1) {
  
    // same row
    stack<int> st;
    st.emplace(0);
    a[h1][0] = INF;
    
    for (int i = 1; i <= m; ++i) {
      
      ll cnt = 0;
      while (a[h1][st.top()] < a[h1][i]) {
        cnt++;
        st.pop();
      }
      
      cnt += st.top() > 0;
      
      while (a[h1][st.top()] <= a[h1][i]) {
        st.pop();
      }
      
      st.emplace(i);
      res += cnt + 1;
    }
    

    for (int i = 1; i <= m; ++i) {
      max_without_h1[i] = -INF;
      max_without_h2[i] = val[i] = a[h1][i];
    }
    
    
    for (int h2 = h1 + 1; h2 <= n; ++h2) {
      
      for (int i = 1; i <= m; ++i) {
        // same col
        res += max_without_h1[i] < min(a[h1][i], a[h2][i]);
        
        max_without_h1[i] = max(max_without_h1[i], a[h2][i]);
      }
      
      
      stack<int> st;
      st.emplace(0);
      
      
      for (int i = 1; i <= m; ++i) {
        
        ll cnt = 0;
        
        val[i] = max(val[i], a[h2][i]);
        
        while (val[st.top()] < val[i]) {
          int j = st.top();
          cnt += max_without_h1[j] < min(a[h1][j], a[h2][i]) 
              && max_without_h2[i] < min(a[h1][j], a[h2][i]);
          st.pop();
        }
        
        int j = st.top();
        if (j) cnt += max_without_h1[j] < min(a[h1][j], a[h2][i]) 
                   && max_without_h2[i] < min(a[h1][j], a[h2][i]);
        
        while (val[st.top()] <= val[i]) {
          st.pop();
        }
        
        st.emplace(i);
        
        // (h2, i) as bottom row
        if (max_without_h2[i] < a[h2][i]) {
          res += cnt;
        }
        
        max_without_h2[i] = max(max_without_h2[i], a[h2][i]);
        
      }
      
    }
    
    
  }
  
  
  cout << res;  
  
  

	return 0;
}


