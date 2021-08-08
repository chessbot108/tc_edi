/*
* Try to get from node 1 to node n, each edge has a weight, and a flow
* need to have weights less than K, but with max flow
* flow is the min flow of all edges in path
* also one edge might be deleted, calculate max flow in worst case possible
* N(logN)^2, logN for binary search, NlogN for dij/segment tree
* very hard
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <queue>
#include <memory.h>
using namespace std;
#define MAXN 20001
#define MAX_INT 2000000000
vector<int> adj[MAXN];
pair<int, int> removed = { -1, -1 };
map<pair<int, int>, int> wt, flow, ind;
map<pair<int, int>, bool> is_path;
vector<pair<int, int> > edges, path;
int dist[MAXN], end_dist[MAXN], par[MAXN], npar[MAXN], st[4*MAXN], llast[2*MAXN], rfirst[2*MAXN];
int N, M, K;

void update(int l, int r, int ul, int ur, int si, int val)
{
	if (ur < ul) return;
	if (ul <= l && r <= ur)
	{
		st[si] = min(st[si], val);
		return;
	}
	if (ul > r || l > ur) return;

	int m = (l + r) / 2;
	update(l, m, ul, ur, 2 * si + 1, val);
	update(m + 1, r, ul, ur, 2 * si + 2, val);
}

int query(int l, int r, int si, int e)
{
	if (l == r) return st[si];

	int m = (l + r) / 2;
	return min(st[si], e <= m ? query(l, m, 2 * si + 1, e) : query(m + 1, r, 2 * si + 2, e));
}

bool init_dij(int min_flow, int n)
{
	priority_queue<pair<int, int> > vis;
	end_dist[n] = 0;
	vis.push({ 0, n });

	while (vis.size())
	{
		int curr = vis.top().second;
		int distance = -vis.top().first;
		vis.pop();

		if (!curr && distance <= K) return true;
		else if (!curr) return false;

		for (int c : adj[curr])
		{
			if (c == par[curr]) continue;
			if ((end_dist[c] == MAX_INT || end_dist[curr] + wt[{curr, c}] < end_dist[c]) && flow[{curr, c}] <= min_flow)
			{
				end_dist[c] = end_dist[curr] + wt[{curr, c}];
				vis.push({ -end_dist[c], c });
				par[c] = curr;
			}
		}
	}

	return false;
}

void main_dij(int min_flow, int n)
{
	priority_queue<pair<int, pair<int, int> > > vis;
	set<pair<int, int> > used;
	vis.push({ 0, { n, -1 }});

	if (n == N - 1)
	{
		end_dist[n] = 0;
		while (vis.size())
		{
			int curr = vis.top().second.first;
			int prev = vis.top().second.second;
			vis.pop();

			for (int c : adj[curr])
			{
				if (c == par[curr]) continue;
				if (flow[{curr, c}] > min_flow) continue;

				if (end_dist[c] == MAX_INT || end_dist[curr] + wt[{curr, c}] < end_dist[c])
				{
					if (prev == -1 && !is_path[{curr, c}])
					{
						rfirst[ind[{curr, c}]] = path.size() + 1;
						rfirst[ind[{c, curr}]] = path.size() + 1;
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
					else if (!is_path[{curr, c}])
					{
						rfirst[ind[{curr, c}]] = rfirst[ind[{ prev, curr }]] - is_path[{prev, curr}];
						rfirst[ind[{c, curr}]] = rfirst[ind[{ prev, curr }]] - is_path[{prev, curr}];
						used.insert({ curr, c });
						used.insert({ c, curr });
					}

					end_dist[c] = end_dist[curr] + wt[{curr, c}];
					vis.push({ -end_dist[c], { c, curr } });
					par[c] = curr;
				}

				if (used.find({ c, curr }) == used.end())
					if (prev == -1 && !is_path[{curr, c}])
					{
						rfirst[ind[{curr, c}]] = path.size() + 1;
						rfirst[ind[{c, curr}]] = path.size() + 1;
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
					else if (!is_path[{curr, c}])
					{
						rfirst[ind[{curr, c}]] = rfirst[ind[{ prev, curr }]] - is_path[{prev, curr}];
						rfirst[ind[{c, curr}]] = rfirst[ind[{ prev, curr }]] - is_path[{prev, curr}];
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
			}
		}
	}
	else
	{
		dist[n] = 0;
		while (vis.size())
		{
			int curr = vis.top().second.first;
			int prev = vis.top().second.second;
			vis.pop();

			for (int c : adj[curr])
			{
				if (curr == 5 && c == 3)
					dist[0] = 0;
				if (c == npar[curr]) continue;
				if (flow[{curr, c}] > min_flow) continue;

				if ((dist[c] == MAX_INT || dist[curr] + wt[{curr, c}] < dist[c]))
				{
					if (prev == -1 && !is_path[{curr, c}])
					{
						llast[ind[{curr, c}]] = 0;
						llast[ind[{c, curr}]] = 0;
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
					else if (!is_path[{curr, c}])
					{
						llast[ind[{curr, c}]] = llast[ind[{ prev, curr }]] + is_path[{prev, curr}];
						llast[ind[{c, curr}]] = llast[ind[{ prev, curr }]] + is_path[{prev, curr}];
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
					dist[c] = dist[curr] + wt[{curr, c}];
					vis.push({ -dist[c], { c, curr } });
					npar[curr] = c;
				}

				if (used.find({ c, curr }) == used.end())
					if (prev == -1 && !is_path[{curr, c}])
					{
						llast[ind[{curr, c}]] = 0;
						llast[ind[{c, curr}]] = 0;
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
					else if (!is_path[{curr, c}])
					{
						llast[ind[{curr, c}]] = llast[ind[{ prev, curr }]] - is_path[{prev, curr}];
						llast[ind[{c, curr}]] = llast[ind[{ prev, curr }]] - is_path[{prev, curr}];
						used.insert({ curr, c });
						used.insert({ c, curr });
					}
			}
		}
	}
}

int main() {
	for (int t = 1; t <= 10; t++)
	{
		ofstream cout(to_string(t) + ".out");
		ifstream cin(to_string(t) + ".in");
		edges.clear();
		path.clear();
		wt.clear();
		flow.clear();
		ind.clear();
		memset(llast, 0, sizeof llast);
		memset(rfirst, 0, sizeof rfirst);
		for (int i = 0; i < MAXN; i++) adj[i].clear();

		cin >> N >> M >> K;

		for (int i = 0; i < M; i++)
		{
			int a, b, w, f;
			cin >> a >> b >> w >> f;

			adj[--a].push_back(--b);
			adj[b].push_back(a);
			edges.push_back({ a, b });
			edges.push_back({ b, a });
			ind[{a, b}] = edges.size() - 2;
			ind[{b, a}] = edges.size() - 1;

			wt[{a, b}] = w;
			wt[{b, a}] = w;
			flow[{a, b}] = f;
			flow[{b, a}] = f;
			is_path[{a, b}] = false;
			is_path[{b, a}] = false;
		}

		int lo = 0;
		int hi = 1e9;
		while (lo + 1 < hi)
		{
			memset(llast, 0, sizeof llast);
			memset(rfirst, 0, sizeof rfirst);
			int m = (lo + hi) / 2;

			//reset everything
			path.clear();
			is_path.clear();
			memset(par, -1, sizeof par);
			memset(npar, -1, sizeof npar);
			fill(end_dist, end_dist + MAXN, MAX_INT);
			fill(dist, dist + MAXN, MAX_INT);
			fill(st, st + 4 * MAXN, MAX_INT);

			if (!init_dij(m, N - 1))
			{
				lo = m;
				continue;
			}

			int n = 0;
			while (n != N - 1)
			{
				int prev = n;
				n = par[n];

				if (n == prev) break;
				path.push_back({ prev, n });
				is_path[{ prev, n }] = true;
				is_path[{ n, prev }] = true;

				llast[ind[{n, prev}]] = path.size();
				llast[ind[{prev, n}]] = path.size();
				rfirst[ind[{n, prev}]] = path.size();
				rfirst[ind[{prev, n}]] = path.size();
			}

			memset(par, -1, sizeof par);
			memset(npar, -1, sizeof npar);
			fill(end_dist, end_dist + MAXN, MAX_INT);
			fill(dist, dist + MAXN, MAX_INT);
			main_dij(m, N - 1);
			main_dij(m, 0);

			for (int i = 0; i < edges.size(); i++)
			{
				if (flow[edges[i]] > m || is_path[edges[i]]) continue;
				if (m == 531250000)
					dist[0] = 0;
				update(0, path.size() + 1, llast[i], rfirst[i], 0, wt[edges[i]] + min(dist[edges[i].first]  + end_dist[edges[i].second], dist[edges[i].second] + end_dist[edges[i].first]));
			}

			int bin_ans = 0;
			for (int i = 0; i < path.size(); i++)
				bin_ans = max(bin_ans, query(0, path.size() + 1, 0, i + 1));

			if (bin_ans > K)
				lo = m;
			else
				hi = m;
		}

		cout << hi << "\n";
	}
	return 0;
}
