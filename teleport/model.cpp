/*
* bfs with walls and stuff
* also there are one way teleporters which can chain together
* N^2
* medium
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
using namespace std;
#define MAXN 1001
string grid[MAXN];
pair<int, int> par[MAXN][MAXN];
int ans[MAXN][MAXN];
bool vis[MAXN][MAXN]; //for bfs

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

pair<int, int> find(pair<int, int> p)
{
	if (p.first > 1000)
	{
		p.first = 1000;
	}
	return par[p.first][p.second] = (par[p.first][p.second] == p ? p : find(par[p.first][p.second]));
}

int main() {
	for (int t = 1; t <= 10; t++)
	{
		ofstream cout(to_string(t) + ".out");
		ifstream cin(to_string(t) + ".in");
		memset(par, 0, sizeof par);
		memset(vis, false, sizeof vis);
		memset(ans, 0, sizeof ans);

		int N, M, K;
		cin >> N >> M >> K;

		for (int i = 0; i < N; i++)
			cin >> grid[i];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				par[i][j] = { i, j };

		for (int i = 0; i < K; i++)
		{
			int ax, ay, bx, by;
			cin >> ax >> ay >> bx >> by;

			par[--ax][--ay] = par[--bx][--by];
		}
		
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				find({ i, j });

		queue<pair<int, int> > q;
		q.push({ 0, 0 });
		ans[0][0] = 0;
		vis[0][0] = true;

		while (q.size())
		{
			pair<int, int> curr = q.front();
			q.pop();
			vis[curr.first][curr.second] = true;

			for (int d = 0; d < 4; d++)
			{
				int newx = curr.first + dx[d];
				int newy = curr.second + dy[d];

				pair<int, int> end_pair = find({ newx, newy });
				if (newx >= 0 && newx < N && newy >= 0 && newy < M && grid[newx][newy] != '#' && !vis[end_pair.first][end_pair.second])
				{
					vis[end_pair.first][end_pair.second] = true;

					q.push(end_pair);
					ans[end_pair.first][end_pair.second] = ans[curr.first][curr.second] + 1;
				}
			}
		}

		cout << ans[N - 1][M - 1] << "\n";
	}
	return 0;
}
