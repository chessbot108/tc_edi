// find worst case runtime(operations) for model solution

// number of ops = sum over all pairs (a,b) such that a | b 
// ( min(max(freq(a),freq(b)), min(freq(a),freq(b))*log(freq(a) or freq(b)(basically the same))) )

// idea is to have the first half have numbers 1...sqrt(max) have frequency xlogx 
// and then the last half have rest of the numbers
// have high number of divisors (1/2 will pair up with 1...sqrt(max)) and frequency x
// sum of frequencies = n ofc

// ops ~= (sum of the number of divisors in the last half) / 2 * xlogx


#include<bits/stdc++.h> 
using namespace std;

const int maxn = 1e7;
const int maxa = 1e7;
const int first_half = sqrt(maxa);
int divisors[maxa + 1];
vector<pair<int, int>> max_divisors; // divisors[i], i
pair<pair<long long, int>, pair<long long, int>> worst_case; // {operations, num of nums in last_half} , {tot pairs, x}
// FUCK worst case is : 3813918511 46773 3693978 144

int main() {
	// sieve 
	for (int i = 1; i <= maxa; i++)
	{
		for (int j = i; j <= maxa; j += i)
		{
			divisors[j]++;
		}
	}

	for (int i = 1; i <= maxa; i++)
	{
		max_divisors.push_back({ divisors[i],i });
	}

	sort(max_divisors.begin(), max_divisors.end(), greater<pair<int, int>>());

	// test k
	for (int last_half = 1, tot_pairs = 0; last_half <= min(maxa, maxn - first_half); last_half++)
	{
		tot_pairs += max_divisors[last_half - 1].first / 2;

		int x = maxn / (first_half + last_half);

		worst_case = max(worst_case, { {tot_pairs * x , last_half}, {tot_pairs,x } });
	}

	cout << worst_case.first.first << ' ' << worst_case.first.second << ' ' <<
		worst_case.second.first << ' ' << worst_case.second.second << '\n';
}