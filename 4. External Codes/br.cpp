#include <bits/stdc++.h>
using namespace std;

const int N = 105;
long long cnt[300][N], n;
vector < pair <char, int> > v[N];

void process(string s) {
    int r = 0;
    while (r < s.size() && s[r] == s[0]) {
        r++; cnt[s[0]][99]++;
    }
    for (int i = r; i < s.size(); i++) {
        int Pow = 99 - i + r - 1;
        cnt[s[i]][Pow]++;
    }
}

int main() {
    freopen ("br.inp", "r", stdin);
    freopen ("br.out", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        process(s);
    }

    for (int x = 0; x < 99; x++) {
        cnt['B'][x+1] += cnt['B'][x] / 2;
        cnt['B'][x] %= 2;
        cnt['R'][x+1] += cnt['R'][x] / 2;
        cnt['R'][x] %= 2;
    }

    for (int x = 99; x >= 0; x--) {
        if (cnt['B'][x] == cnt['R'][x])
            continue;
        if (cnt['B'][x] > cnt['R'][x])
            return (!(cout << 'B'));
        else
            return (!(cout << 'R'));
    }

    cout << 'R' << '\n';

    return 0;
}
