#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;
const int MX = sqrt(2e9) +10; //around 45000
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int T; cin >> T;
	while(T--){
		int X, temp; cin >> X >> temp;
		assert(temp == 1);
		int a = -1, b = -1, found = 0; 
		for(int k = 1; k<=MX; k++){ //for all X, the length no exceed sqrt(2*X), or sqrt(2e9)
			int s = ((k * (k - 1))/2);
			if(s > X) break; //sanity check
			if((X - s)%k == 0){
				a = (X - s)/k, b = a + k; 
			}
		}
		
		if(a == 0){
			a++; //just an edge case, starting from 0 and starting at 1 are the same
		}
		if(X&(X-1)) cout << a << " " << b << "\n";	
		else cout << "-1 -1\n";
	}

	return 0;
}
