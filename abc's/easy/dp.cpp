/*
* a game where you play A, B, C
* player knows oppenets moves, gets a point everytime plays a card the opponent has placed at least the most(ties included)
* tries to get most points
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define MAXN 100001

//cant switch cards, must choose only one to play O(N) very easy
/*
int main() {
	for (int t = 1; t <= 10; t++)
	{
		ofstream cout(to_string(t) + ".out");
		ifstream cin(to_string(t) + ".in");

		int N;
		cin >> N;

		string s;
		cin >> s;

		int a = 0, b = 0, c = 0;
		int ansa = 0, ansb = 0, ansc = 0;
		for (int i = 0; i < N; i++)
		{
			if (s[i] == 'A') a++;
			if (s[i] == 'B') b++;
			if (s[i] == 'C') c++;

			int max_used = max(max(a, b), c);

			if (a == max_used) ansa++;
			if (b == max_used) ansb++;
			if (c == max_used) ansc++;
		}

		cout << max(max(ansa, ansb), ansc) << "\n";
	}
	return 0;
}
*/


//can switch, but only after K consecutive same card I only know O(N*K) but there is prob a better alg medium/hard

int dp[MAXN][3]; //max points if ends in letter j at index i
int dp_max[MAXN];
int pre[MAXN][3];
int val[3];

int main() {
	for (int t = 1; t <= 10; t++)
	{
		ofstream cout(to_string(t) + ".out");
		ifstream cin(to_string(t) + ".in");

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
			if (i == N)
				for (; ind < N; ind++)
					for (int j = 0; j < 3; j++)
						val[j] = max(val[j], dp_max[ind] - pre[ind][j]);
			else
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
	}
	return 0;
}

