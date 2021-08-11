#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
using namespace std;

ll n, k;


int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
		while(T--){
				n = inf.readInt();
				k = inf.readInt();
				assert(k == 1);
				ll a = ouf.readInt(-1, n), b = ouf.readInt(-1, n);
				if(a == -1 && b == -1){
					if((n)&(n-1))
						quitf(_wa, "Judger found an answer but participant did not");
				}else{
					if(a < 1) quitf(_wa, "a should be greater than 1");
					if(a >= b) quitf(_wa, "a should be strictly less than b");
					if(b > n) quitf(_wa, "b should be less than or equal to n");
					int bad = 0;
					if(b - a > 1e6) bad = 1;
					ll tot = 0;
					for(ll i = a; i<b && !bad; i++){
						tot += i;
					}
					if(tot != n || bad){
						quitf(_wa, "sum of integers [%d, %d) is not %d", a, b, n);
					}
				}				
		}
		quitf(_ok, "n=%d", n);

}
