#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  long long N, X;
  cin >> N >> X;
  
  vector<pair<long long, long long> > A;
  for (int i = 0; i < N; i++)
  {
    long long a, b;
    cin >> a >> b;
    
    A.push_back({a, b});
  }
  
  long long lo = 0;
  long long hi = 1e15 + 1;
  sort(A.begin(), A.end());
  while (lo + 1 < hi)
  {
    long long m = (lo + hi)/2;
    long long money = 0;
    for (int i = 0; i < N; i++)
    {
      money += max((long long)0, (m - A[i].first))/A[i].second;
      if (money >= X) break;
    }
    
    if (money >= X)
      hi = m;
    else
      lo = m;
  }
  
  cout << hi << "\n";
  return 0;
}