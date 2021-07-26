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
#include <cassert>
using namespace std;
#define MAXN 1001
string grid[MAXN];
pair<int, int> par[MAXN][MAXN];
int ans[MAXN][MAXN];
bool vis[MAXN][MAXN]; //for bfs
queue<pair<int, int> > q;
int calls = 0;
int N, M, K;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

pair<int, int> find(const pair<int, int> p)
{
	vis[p.first][p.second] = true;
	calls++;
	assert(p.first >= 0 && p.first < N && p.second >= 0 && p.second < M);
	return par[p.first][p.second] = (par[p.first][p.second] == p ? p : find(par[p.first][p.second]));
}

int main() {
	for (int t = 1; t <= 10; t++)
	{
		calls = 0;
		ofstream cout(to_string(t) + ".out");
		ifstream cin(to_string(t) + ".in");
		memset(par, 0, sizeof par);
		memset(vis, false, sizeof vis);
		memset(ans, 0, sizeof ans);

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

		queue<pair<int, int> > q1;
		q = q1;
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

				pair<int, int> end_pair;
				if (newx >= 0 && newx < N && newy >= 0 && newy < M)
					end_pair = find({ newx, newy });

				if (newx >= 0 && newx < N && newy >= 0 && newy < M && grid[newx][newy] != '#' && !vis[end_pair.first][end_pair.second])
				{
					vis[end_pair.first][end_pair.second] = true;

					q.push(end_pair);
					assert(q.size() <= N * M);
					ans[end_pair.first][end_pair.second] = ans[curr.first][curr.second] + 1;
				}
			}
		}

		cout << ans[N - 1][M - 1] << "\n";
	}
	return 0;
}
