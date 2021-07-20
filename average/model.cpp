#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	for (int t = 1; t <= 10; t++)
	{
		ifstream cin(to_string(t) + ".in");
		ofstream cout(to_string(t) + ".out");

		int N;
		cin >> N;

		int sum = 0;
		int mini = 1000000009;
		for (int i = 0; i < N; i++)
		{
			int a;
			cin >> a;

			mini = min(mini, 10 * a);
			sum += 10 * a;
		}

		cout << (double)((sum - mini) / (N - 1)) / 10 << "\n";
	}
}
