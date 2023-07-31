#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int dp[31][5][1 << 4][2];

void madd(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}

int bit(int mask, int i) {
	return mask >> i & 1;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	dp[0][0][0][0] = 1;
	for (int len = 0; len < 30; len++)
		for (int rem = 0; rem < 5; rem++)
			for (int mask = 0; mask < (1 << (k - 1)); mask++)
				for (int pos = 0; pos < 2; pos++) {
					for (int dgt = 0; dgt < (1 << k); dgt++) {
						int sum = 0;
						for (int i = 0; i < k; i++) sum += bit(dgt, i);
						if (bit(sum + rem, 0) != bit(n, len)) continue;
						int nrem = (sum + rem) / 2, nmask = 0;
						int npos = pos || bit(dgt, 0);
						for (int i = 0; i < k - 1; i++)
							if (bit(dgt, i) != bit(dgt, i + 1)) {
								if (bit(dgt, i) < bit(dgt, i + 1))
									nmask += 1 << i;
							}
							else if (bit(mask, i)) nmask += 1 << i;
						madd(dp[len + 1][nrem][nmask][npos],
						dp[len][rem][mask][pos]);
					}
				}
	cout << dp[30][0][(1 << (k - 1)) - 1][1] << '\n';
}