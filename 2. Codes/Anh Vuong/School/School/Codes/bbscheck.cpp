#include <bits/stdc++.h>
using namespace std;

char inv[256];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    stack <char> st; int dep = 0;
    string s; cin >> s;
    inv[')'] = '(';
    inv[']'] = '[';
    inv['}'] = '{';
    st.push('0');
    for (char c : s) {
        if (inv[c]) {
            if (st.top() != inv[c]) {
                cout << "0\n"; return 0;
            }
            st.pop();
        }
        else st.push(c);
        dep = max(dep, int(st.size()));
    }
    st.pop();
    if (st.size()) cout << "0\n";
    else cout << dep - 1 << '\n';
}
