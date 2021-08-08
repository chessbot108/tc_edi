#include<bits/stdc++.h>
using namespace std;

bool fail = 0;

// random number from 0 to 2^64-1 (be careful about it taking unsigned int / long long!)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random number from a to b
long long randint(long long a, long long b)
{
	return uniform_int_distribution<long long>(a, b)(rng);
}


// put constraints under here
const int maxn = 10000;
const int maxw = 1e4;
const int maxk = 1e9;
const int maxf = 1e9;


// print test case to stdout (redirected to file)
void generate_test(int test_num)
{
	vector<string> test_cases;
	int tot_n = 0;
	// generate test cases until constraint (like maxn) is met
	// good idea to generate in largest range of n possible
	while (1)
	{
		set<pair<int, int>> added;

		// assorted n, m, and k
		int n = max(10ll , randint(2, min(100, (int)pow(3.2, (test_num - 1) / 10 + 1)))); // n <= 2 is impossible
		int m = min(randint(1,5)*n, n*(n-1)/randint(3,4));
		int k = randint(randint(1,5)*n*maxw/10, n * maxw); // too large and all paths work, too small and none do

		if (tot_n + n > maxn)
		{
			break;
		}
		else
		{
			tot_n += n;
		}

		test_cases.push_back(to_string(n) + ' ' + to_string(m) + ' ' + to_string(k) + '\n');

		// make tree first
		for (int i = 2; i <= n and m; i++)
		{
			// assorted edge weights
			test_cases.back() += to_string(i-1) + ' ' + to_string(i) + ' ' + to_string(randint(1, randint(1,10)*maxw)) + ' ' + to_string(randint(1, maxf)) + '\n';
			added.insert({ i - 1,i });
			m--;
		}
		
		for (int i = 0; i < m; i++)
		{
			int j = randint(1, n), k = randint(1, n);
			while (j == k or added.count({ min(j, k), max(j, k) }))
			{
				//cerr << j << ' ' << k << '\n';
				j = randint(1, n), k = randint(1, n);
			}
			//cerr << n << ' ' << "added!\n";
			// assorted edge weights
			test_cases.back() += to_string(j) + ' ' + to_string(k) + ' ' + to_string(randint(1, randint(1, 10) * maxw)) + ' ' + to_string(randint(1, maxf)) + '\n';
			
			added.insert({ min(j, k), max(j, k) });
		}
	}
	
	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases)
	{
		cout << test_case;
	}
}


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

// read test case from stdin and print solution to stdout (redirected to file)
void model_sol()
{
	// O(N*(log(n)^2))
	int t; cin >> t;
	while (t--)
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
			cout << -1 << '\n';
			cerr << t << ' ' << "Couldn't find path\n";
		}
		else
		{
			cout << l << '\n';
		}
	}
}


#define MAXN 200
#define MAX_INT 2000000000
vector<int> adjs[MAXN];
pair<int, int> removed = { -1, -1 };
map<pair<int, int>, int> wt, flow, ind;
map<pair<int, int>, bool> is_path;
vector<pair<int, int> > edgess, path;
int dists[MAXN], end_dist[MAXN], parr[MAXN], npar[MAXN], st[4 * MAXN], llast[2 * MAXN], rfirst[2 * MAXN];
int N, M, K;

bool init_dij(int min_flow, int n)
{
	set<pair<int, int> > vis;
	end_dist[n] = 0;
	vis.insert({ 0, n });

	while (vis.size())
	{
		int curr = vis.begin()->second;
		int distance = vis.begin()->first;
		vis.erase(vis.begin());
		if (!curr && distance <= K) return true;
		else if (!curr) return false;

		for (int c : adjs[curr])
		{
			if (c == parr[curr]) continue;
			if ((end_dist[c] == 33686018 || end_dist[curr] + wt[{curr, c}] < end_dist[c]) && flow[{curr, c}] <= min_flow && make_pair(curr, c) != removed && make_pair(c, curr) != removed)
			{
				end_dist[c] = end_dist[curr] + wt[{curr, c}];
				vis.insert({ end_dist[c], c });
				parr[c] = curr;
			}
		}
	}

	return false;
}

// read test case from stin and print solution to stdout (redirected to file)
void brute_sol()
{
	int t; cin >> t;
	while (t--)
	{
		cin >> N >> M >> K;
		// cerr << N << ' ' << M << ' ' << K << '\n';

		for (int i = 0; i < M; i++)
		{
			int a, b, w, f;
			cin >> a >> b >> w >> f;

			adjs[--a].push_back(--b);
			adjs[b].push_back(a);
			edgess.push_back({ a, b });
			edgess.push_back({ b, a });
			ind[{a, b}] = edgess.size() - 2;
			ind[{b, a}] = edgess.size() - 1;

			wt[{a, b}] = w;
			wt[{b, a}] = w;
			flow[{a, b}] = f;
			flow[{b, a}] = f;
			is_path[{a, b}] = false;
			is_path[{b, a}] = false;
		}

		int lo = 0;
		int hi = 1e9+1;
		while (lo + 1 < hi)
		{
			int m = (lo + hi) / 2;

			//reset everything
			path.clear();
			is_path.clear();
			memset(parr, -1, sizeof parr);
			memset(npar, -1, sizeof npar);
			fill(end_dist, end_dist + MAXN, MAX_INT);
			fill(dists, dists + MAXN, MAX_INT);
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
				n = parr[n];

				if (n == prev) break;
				path.push_back({ prev, n });
				is_path[{ prev, n }] = true;
				is_path[{ n, prev }] = true;

				llast[ind[{n, prev}]] = path.size() - 2;
				llast[ind[{prev, n}]] = path.size() - 2;
				rfirst[ind[{n, prev}]] = path.size() - 1;
				rfirst[ind[{prev, n}]] = path.size() - 1;

			}

			memset(parr, -1, sizeof parr);
			memset(npar, -1, sizeof npar);
			memset(end_dist, 2, sizeof end_dist);
			memset(dists, 2, sizeof dists);

			int bin_ans = 0;
			bool works = true;
			for (int i = 0; i < path.size(); i++)
			{
				removed = path[i];

				if (!init_dij(m, N - 1))
				{
					lo = m;
					works = false;
					break;
				}
				memset(end_dist, 2, sizeof end_dist);
			}

			if (works)
				hi = m;
		}

		if (hi == 1e9 + 1)
		{
			cout << -1 << '\n';
		}
		else
		{
			cout << hi << "\n";
		}
		// reset variables
		for (int i = 0; i < MAXN; i++)
		{
			adjs[i].clear();
		}
		edgess.clear();
		wt.clear();
		flow.clear();
		ind.clear();
		is_path.clear();
		removed = { -1, -1 };
		path.clear();
		is_path.clear();
		memset(dists, 0, sizeof(dists));
		memset(end_dist, 0, sizeof(end_dist));
		memset(parr, 0, sizeof(parr));
		memset(npar, 0, sizeof(npar));
		memset(st, 0, sizeof(st));
		memset(llast, 0, sizeof(llast));
		memset(rfirst, 0, sizeof(rfirst));
	}
}

// for checking tests look right
void read_and_print_file(string directory, string name)
{
	freopen((directory + name).c_str(), "r", stdin);

	string a;
	while (getline(cin, a))
	{
		cout << a << '\n';
	}

	exit(0);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int num_tests = 50;

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Other's Problems\Sol's Problem Writing Meeting\Checking Model with Brute Tests\)";

	// read_and_print_file(directory, "1.in"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		cerr << "Test: " << test_num << " started" << '\n';

		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);

		// generate the output for the model
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "model" + ".out").c_str(), "w", stdout);
		model_sol();
		fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer
		// generate the output for the brute
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "brute" + ".out").c_str(), "w", stdout);
		brute_sol();
		fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer

		vector<string> model_output, brute_output;
		string temp;

		// read output for the model
		ifstream fin((directory + to_string(test_num) + "model" + ".out").c_str());
		while (fin >> temp)
		{
			model_output.push_back(temp);
		}
		fin.close();
		// read output for the brute
		fin.open((directory + to_string(test_num) + "brute" + ".out").c_str());
		while (fin >> temp)
		{
			brute_output.push_back(temp);
		}
		fin.close();

		// compare outputs
		cerr << "model and brute sizes: " << model_output.size() << ' ' << brute_output.size() << '\n';
		for (int i = 0; i < min(model_output.size(), brute_output.size()); i++)
		{

			if (model_output[i] != brute_output[i])
			{
				cerr << "The model and the brute do not agree!\n";
				cerr << "Differ Test: " << test_num << '\n';
				cerr << "Differ Index: " << i << '\n';
				cerr << "Differ Values: " << model_output[i] << ' ' << brute_output[i] << '\n';
				fail = 1;
			}
		}

		cerr << "Test: " << test_num << " completed" << '\n';
	}

	if (!fail) {
		cerr << "The model and the brute agree!\n";
	}
}