#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int N;
	cin >> N;

	int sum = 0;
	int mini = 1000000009;
	for (int i = 0; i < N; i++)
	{
		int a;
		cin >> a;

		mini = min(mini, 10 * a); // we do 10*a to get tenth
		sum += 10 * a; // multiply by 10 to round down to tenth
	}

	cout << ((sum - mini) / (N - 1)) / 10 << "." << ((sum - mini) / (N - 1)) % 10 << "\n";
}
