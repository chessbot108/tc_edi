//gyrating cat enthusiast
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <set>

#define ll long long
#define lb long double
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define ins insert
#define cont continue
#define siz(vec) ((int)(vec.size()))

#define LC(n) (((n) << 1) + 1)
#define RC(n) (((n) << 1) + 2)
#define init(arr, val) memset(arr, val, sizeof(arr))
#define bckt(arr, val, sz) memset(arr, val, sizeof(arr[0]) * (sz+5))
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define tern(a, b, c) ((a) ? (b) : (c))
#define feq(a, b) (fabs(a - b) < eps)
#define abs(x) tern((x) > 0, x, -(x))

#define moo printf
#define oom scanf
#define mool puts("") 
#define orz assert
#define fll fflush(stdout)

const lb eps = 1e-9;
const ll mod = 1e9 + 7, ll_max = (ll)1e18;
const int MX = 10000 +10, int_max = 0x3f3f3f3f;

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, pii>> edges;

int par[MX], n, m;

int find(int x){ if(x != par[x]) par[x] = find(par[x]); return par[x]; }
void Union(int a, int b){ a = find(a), b = find(b); par[a] = b; }
void mkdsu(){ for(int i = 0; i<=max(n*n, m*m); i++) par[i] = i; }

int sqsum(int x){
	return (x * (x + 1) * (2*x + 1))/6;
}

int cbsum(int x){
	int t = (x * (x+1))/2;
	return t*t;
}

int eval(int x){
	return (cbsum(x) - cbsum(x/2)) * 2 + (((x%2)^1) * (x/2) * (x/2) * (x/2));
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);
	int T; cin >> T;
	//for(int z = 1; z<T; z++){
	//for(int q = 1; q<T; q++){
	while(T--){
		edges.clear();
		//n = z; m = q;
		cin >> n >> m;
			if(n > m) swap(n, m);
		mkdsu();
		for(int a = 0; a<n; a++){
			for(int b = 0; b<m; b++){
				for(int c = 0; c<n; c++){
					for(int d = 0; d<m; d++){
						int A = a*m +b, B = c*m +d, C = abs(a - c), D = abs(d - b);
						edges.pb(mp((C*C*C) + (D*D*D), mp(A, B)));
					}
				}
			}
		}
		sort(edges.begin(), edges.end());
		moo("%d\n", siz(edges));
		ll ans = 0;
		for(int i = siz(edges) -1; ~i; i--){
			int u = edges[i].second.first, v=  edges[i].second.second, w = edges[i].first;	
			moo("%d: %d %d, %d %d: %d\n", (int)(find(u) == find(v)), u/m, u%m, v/m, v%m, w);
			if(find(u) != find(v)){
				ans += (ll)w;
				Union(u, v);
			}
		}
		n--, m--;
		ll ans2 = 0;

		//for(int a = 0; a<=n; a++){
		//for(int b = 0; b<=m; b++){
		//int A = max(a, n-a), B = max(b, m-b);
		//ans2 += A*A*A + B*B*B;
		//}
		//}
		//ll temp = (sqsum(n) - sqsum(n/2)) * 2 + (((n%2)^1) * (n/2) * (n/2));

		//moo("%lld %lld\n", ans2, temp * (m + 1));
		ans2 = eval(n)*(m+1) + eval(m)*(n+1);
		ans2 -= 2 * (n*n*n + m*m*m);
		ans2 += max(m*m*m + (n/2)*(n/2)*(n/2), n*n*n + (m/2)*(m/2)*(m/2));
		moo("%d, %d....ans: %lld %lld\n", n, m, ans, ans2);
		assert(ans == ans2);

	}
//}
//}
	return 0;
}


