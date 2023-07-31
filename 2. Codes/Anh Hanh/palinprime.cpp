#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "palinprime";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int p(int x) {
	if (x > 1e7) return 0;
	if (x <= 1) return 0;
	for (int i = 2; i * i <= x; ++i) if (x % i == 0) return 0;
	return 1;
}
int createPalindrome(int input, int b, bool isOdd)
{
    int n = input;
    int palin = input;
 
    if (isOdd)
        n /= b;
 
    while (n > 0)
    {
        palin = palin * b + (n % b);
        n /= b;
    }
    return palin;
}
 
void generatePalindromes(int l, int r)
{
    int number;
 		ll res = 0;
    for (int j = 0; j < 2; j++)
    {
        int i = 1;
        while ((number = createPalindrome(i, 10, j % 2)) <= r)
        {
        	if (number >= l && p(number)) res += number;
          i++;
        }
    }
    cout << res;
}
 
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int l, r; cin >> l >> r;
	generatePalindromes(l, r);
	return 0;
}

