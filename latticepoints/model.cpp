#include <iostream>
using namespace std;
int main(){
	cin.tie(0) -> sync_with_stdio(0);
	int T; cin >> T;
	while(T--){
		int a, b; cin >> a >> b;
		cout << max(a, b) << " " << ((a == b) ? 3 : 1) << "\n";
	}
	return 0;
}	
