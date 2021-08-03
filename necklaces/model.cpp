#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 400001

int main() {
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
				b.insert(-a); //insert negatives to get largest val smaller
				e.insert(a);
		}

		if (c == 'Q')
			cout << *e.upper_bound(a - 1) + *b.lower_bound(-a + 1) << "\n";
	}
	return 0;
}
