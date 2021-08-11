#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
using namespace std;
#define MAXN 1000
string grid[MAXN];
map<pair<int, int>, pair<int, int> > par;
int ans[MAXN][MAXN];
map<pair<int, int>, int> r; //rank for dsu
bool vis[MAXN][MAXN]; //for bfs

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

pair<int, int> find(pair<int, int> p)
{
	return (par[p] == p ? p : find(par[p]));
}

int main() {
	int N, M, K;
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++)
		cin >> grid[i];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			par[{i, j}] = { i, j };

	for (int i = 0; i < K; i++)
	{
		int ax, ay, bx, by;
		cin >> ax >> ay >> bx >> by;

		par[{--ax, --ay}] = par[{ --bx, --by }];
	}
		
	for (auto p : par)
		find(p.first);

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
	return 0;
}
