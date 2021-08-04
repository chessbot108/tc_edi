#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define MAXN 100001

int dp[MAXN][3]; //max points if ends in letter j at index i
int dp_max[MAXN];
int pre[MAXN][3];
int val[3];

int main() {
	memset(dp_max, 0, sizeof dp_max);
	memset(dp, 0, sizeof dp);
	memset(pre, 0, sizeof pre);
	memset(val , 0, sizeof val);


	int N, K;
	cin >> N >> K;
	string s;
	cin >> s;

	int a = 0, b = 0, c = 0;
	for (int i = 1; i <= N; i++)
	{
		if (s[i - 1] == 'A') a++;
		if (s[i - 1] == 'B') b++;
		if (s[i - 1] == 'C') c++;

		int max_used = max(max(a, b), c);

		for (int j = 0; j < 3; j++) pre[i][j] = pre[i - 1][j];
		if (a == max_used) pre[i][0]++;
		if (b == max_used) pre[i][1]++;
		if (c == max_used) pre[i][2]++;
	}

	for (int i = 0; i <= min(2 * K, N); i++)
	{
		for (int k = 0; k < 3; k++)
			dp[i][k] = pre[i][k];
		dp_max[i] = max(max(dp[i][0], dp[i][1]), dp[i][2]);
	}

	int ind = K;
	for (int i = min(2 * K, N); i <= N; i++)
	{
		if (i == N) //case 2
			for (; ind < N; ind++)
				for (int j = 0; j < 3; j++)
					val[j] = max(val[j], dp_max[ind] - pre[ind][j]);
		else // case 1
		{
			for (int j = 0; j < 3; j++)
				val[j] = max(val[j], dp_max[ind] - pre[ind][j]);
			ind++;
		}

		for (int j = 0; j < 3; j++)
			dp[i][j] = max(dp[i][j], pre[i][j] + val[j]);
		dp_max[i] = max(max(dp[i][0], dp[i][1]), dp[i][2]);
	}

	cout << max(max(dp[N][0], dp[N][1]), dp[N][2]) << "\n";
	return 0;
}

