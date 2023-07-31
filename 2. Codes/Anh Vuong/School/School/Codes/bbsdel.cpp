#include <bits/stdc++.h>
using namespace std;

char s[105];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> (s + 1);
    int n = strlen(s + 1);
    vector <int> p, q;
    p.push_back(1); int d = 0;
    string ans;
    while (true) {
        q.clear();
        for (int i : p) {
            int dd = 0;
            for (int j = i; j <= n; j++) {
                if (dd < 0) break;
                if (!dd && s[j] == '(')
                    q.push_back(j + 1);
                dd += s[j] == '(' ? 1 : -1;
            }
        }
        if (q.size()) {
            ans += '('; d++;
        }
        else {
            for (int i : p) {
                int dd = 0;
                for (int j = i; j <= n; j++) {
                    if (dd < 0) break;
                    if (!dd && s[j] == ')')
                        q.push_back(j + 1);
                    dd += s[j] == '(' ? 1 : -1;
                }
            }
            if (!q.size()) break;
            ans += ')'; d--;
        }
        if (!d) break;
        swap(p, q);
    }
    cout << ans << '\n';
}