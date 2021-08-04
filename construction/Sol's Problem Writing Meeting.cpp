// O(N*(log(n)^2))
#include<bits/stdc++.h>
using namespace std;

const int maxn = 5e4;
vector<tuple<int, int, int, int>> edges;
vector<tuple<int, int>> adj[maxn];
int dist[2][maxn];
int par[maxn];
bool on_path[maxn];
int interval[maxn][2]; // 0 = from end 1 = from start | For IOD
int n, m, k, ans;

// it's fine to find the longest index on the path because 
void dijkstra(int start, int dist[], int find_index_on_path) {
	fill(dist, dist + n, 1e9 + 1);

	// first dijkstra to find the main path
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
	pq.push({ 0,start });
	dist[start] = 0;
	while (!pq.empty())
	{
		auto c = pq.top(); pq.pop();
		int d = c[0];
		int curr = c[1];

		if (d == dist[curr])
		{
			for (auto& [ne, w] : adj[curr])
			{
				if (dist[ne] > d + w)
				{
					dist[ne] = d + w;

					par[ne] = curr;

					if (find_index_on_path and not on_path[ne])
					{
						interval[ne][find_index_on_path - 1] = interval[curr][find_index_on_path - 1];
					}

					pq.push({ dist[ne], ne });
				}
			}
		}
	}
	//cout << "finished\n";
}

bool can_meet(int max_anger)
{
	int min_max_path = -1;

	for (int i = 0; i < n; i++)
	{
		adj[i].clear();
	}
	memset(par, 0, sizeof(par));
	memset(on_path, 0, sizeof(on_path));
	memset(interval, 0, sizeof(interval));

	// create adj matrix
	for (auto [a, b, w, f] : edges)
	{
		if (f <= max_anger)
		{
			// cout << a << ' ' << b << ' ' << w << ' ' << f << '\n';
			adj[a].push_back({ b,w });
			adj[b].push_back({ a,w });
		}
	}

	// dijkstra
	dijkstra(0, dist[1], 0);
	if (dist[1][n - 1] == 1e9 + 1)
	{
		//cout << "hi\n";
		return 0;
	}

	// get path
	int curr = n - 1;
	int idx = 0;
	while (1)
	{
		//cout << curr << '\n';
		on_path[curr] = 1;

		interval[curr][0] = idx; // base case for IOD dp
		interval[curr][1] = idx;

		if (curr == 0)
		{
			break;
		}
		curr = par[curr];
		idx += 1;
	}

	dijkstra(n - 1, dist[0], 1); // dijkstra to get start of IOD
	dijkstra(0, dist[1], 2); // dijkstra to get end of IOD

	//cout << "hi\n";
	// create events
	vector<pair<int, int>> events; // events trick to add and remove active events
	// "direction" matters here so both a,b and b,a considered
	for (int a = 0; a < n; a++)
	{
		for (auto [b, w] : adj[a])
		{
			if (interval[a][0] < interval[b][1])
			{
				if (on_path[a] and on_path[b] and par[a] == b)
				{
					// rare case of edge on the original main shortest path
					continue;
				}
				// edge not on path
				int len_path = dist[0][a] + w + dist[1][b];

				// cout << a << ' ' << b << ' ' << interval[a][0] << ' ' << interval[b][1] << ' ' << len_path<< '\n';

				events.push_back({ interval[a][0], len_path }); // add event
				events.push_back({ interval[b][1], -len_path }); // remove event
			}
		}
	}
	sort(events.begin(), events.end());

	multiset<int> min_paths; // stores min paths through some edge such that their IODs 
	// contain curr edge to be removed
	// try removing all edges on the path
	for (int i = 0, j = 0; i < idx; i++)
	{
		while (j < events.size() and events[j].first <= i)
		{
			//cout << events[j].first << ' ' << events[j].second << '\n';
			if (events[j].second < 0)
			{
				min_paths.erase(min_paths.find(-events[j].second));
			}
			else
			{
				min_paths.insert(events[j].second);
			}

			j++;
		}

		if (not min_paths.empty())
		{
			// cout << *min_paths.begin() << '\n';
			min_max_path = max(min_max_path, *min_paths.begin());
		}
		else {
			min_max_path = -1;
			break;
		}
	}

	if (min_max_path == -1)
	{
		return 0; // no other path exists
	}
	else {
		return min_max_path <= k;
	}
}

int main()
{
	edges.clear();
	//clock_t start = clock();
	//freopen(R"(C:\Users\elija\Desktop\CODING\Competitive Programming\Problems\Assorted OJ\Teamscode\2021 Summer\problem_8_test_cases\8.in)", "r", stdin);
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++)
	{
		int a, b, w, f;
		cin >> a >> b >> w >> f;
		a--; b--;

		edges.push_back({ a,b,w,f });
	}

	// bin search for min anger
	int l = 0, r = 1e9 + 10;
	while (l != r)
	{
		int m = (l + r) / 2;
		//cout << m << '\n';
		if (can_meet(m))
		{
			r = m;
		}
		else
		{
			l = m + 1;
		}

	}

	if (l == 1e9 + 10)
	{
		cout << -1;
	}
	else
	{
		cout << l << '\n';
	}

	//cout << fixed << setprecision(12) << double(clock() - start) / CLOCKS_PER_SEC << '\n';
}