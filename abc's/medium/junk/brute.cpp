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
		if (i == N)
      for (int j = 0; j < 3; j++)
        for (int k = K; k <= N; k++)
					dp[i][j] = max(dp[i][j], dp_max[k] + pre[i][j] - pre[k][j]);
		else
			for (int j = 0; j < 3; j++)
        for (int k = K; k <= N-K; k++)
					dp[i][j] = max(dp[i][j], dp_max[k] + pre[i][j] - pre[k][j]);
		
		dp_max[i] = max(dp[i][0], max(dp[i][1], dp[i][2]));
	}

	cout << max(max(dp[N][0], dp[N][1]), dp[N][2]) << "\n";
	return 0;
}
