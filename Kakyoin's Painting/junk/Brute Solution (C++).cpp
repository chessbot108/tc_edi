// O(n^2)
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn2 = 1e4+1;
long long dp[maxn2][maxn2][2]; // dp[curr point][num disjoint intervals][interval includes i]
long long fac[maxn2];

int main() 
{
	cin.tie(0)->sync_with_stdio(0);

	// precompute factorials modulo 1e9+7
	fac[0] = 1;
	for (int i = 1; i < maxn2; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
	}

	// solution
	int t, n;

	dp[1][1][1] = 1;
	dp[1][0][0] = 1;
	for (int i = 0; i < maxn2-1; i++) 
	{
		for (int j = 0; j < maxn2-1; j++) 
		{
			dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][1]) % mod; // extend current one
			dp[i + 1][j + 1][1] = (dp[i + 1][j + 1][1] + dp[i][j][0] + dp[i][j][1]) % mod; // start new one
			dp[i + 1][j][0] = (dp[i + 1][j][0] + dp[i][j][0] + dp[i][j][1]) % mod; // end current one(if exists) and don't start new one
		}
	}

	cin >> t;
	while (t--) 
	{
		cin >> n;

		long long ans = 0;
		for (int num_recs = 1; num_recs <= n; num_recs++) 
		{
			long long contribution = num_recs;
			contribution = contribution * (dp[n][num_recs][0] + dp[n][num_recs][1]) % mod;
			contribution = contribution * (dp[n][num_recs][0] + dp[n][num_recs][1]) % mod;
			contribution = contribution * fac[num_recs] % mod;

			ans = (ans + contribution) % mod;
		}

		cout << ans << '\n';
	}
}