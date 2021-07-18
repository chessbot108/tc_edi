#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 100001

//simplest verison, only calc num elements in link, NlogN cuz sets, could be O(n*inv_ack) dsu easy

int main() {
	ifstream cin(to_string(t) + ".in");
	ofstream cout(to_string(t) + ".out");

	int N, M;
	cin >> N >> M;

	set<int> b;
	set<int> e;
	b.insert(0);
	e.insert(N);
	for (int i = 0; i < M; i++)
	{
		char c;
		int a;
		cin >> c >> a;

		if (c == 'R')
		{
			b.insert(-a);
			e.insert(a);
		}

		if (c == 'Q')
			cout << *e.upper_bound(a - 1) + *b.lower_bound(-a + 1) << "\n";
	}
	return 0;
}

