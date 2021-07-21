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
	return par[p] = (par[p] == p ? p : find(par[p]));
}

void merge(pair<int, int> a, pair<int, int> b)
{
	a = find(a);
	b = find(b);
	if (r[a] > r[b])
		par[b] = a;
	else if (r[b] > r[a])
		par[a] = b;
	else
	{
		par[a] = b;
		r[b]++;
	}
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

	queue<pair<int, int> > q;
	q.push({ 0, 0 });
	ans[0][0] = 0;
	vis[0][0] = true;

	while (q.size())
	{
		pair<int, int> curr = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			int newx = curr.first + dx[d];
			int newy = curr.second + dy[d];

			if (newx >= 0 && newx < N && newy >= 0 && newy < N && !vis[newx][newy] && grid[newx][newy] != '#')
			{
				pair<int, int> end_pair = find({ newx, newy });
				vis[end_pair.first][end_pair.second] = true;
				vis[newx][newy] = true;

				q.push(end_pair);
				ans[end_pair.first][end_pair.second] = ans[curr.first][curr.second] + 1;
			}
		}
	}

	cout << ans[N - 1][N - 1] << "\n";
	return 0;
}
