//gyrating cat enthusiast
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <numeric>
#include <map>
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define mp make_pair

typedef long double lb;
typedef long long ll;

const lb eps = 1e-9;
const ll mod = 1e9 + 7, ll_max = (ll)1e18;
const int MX = 2e5 +10, int_max = 0x3f3f3f3f;

using namespace std;

typedef pair<int, int> pii;


//kactl go brrrrrrr
//https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point.h
//https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ConvexHull.h
//https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/PolygonArea.h
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
}; //kactl, Point.h

typedef Point<ll> P;

vector<P> arr;
//note i never edit this array
//instead i use vectors/lists of indeces instead of storing the points themselves
//it's much easier i would think

bool cmp(int a, int b){
	return arr[a] < arr[b];
}


vector<int> convexHull(vector<int> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts), cmp);
	vector<int> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (int p : pts) {
			while (t >= s + 2 && arr[h[t-2]].cross(arr[h[t-1]], arr[p]) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
} //kactl convex hull.h

ll pA2(const vector<int>& v) {
	ll a = arr[v.back()].cross(arr[v[0]]);
	rep(i,0,sz(v)-1) a += arr[v[i]].cross(arr[v[i+1]]);
	return a;
} //kactl polygon area.h

vector<int> removed_ch(const vector<int>& orig, vector<int> rem){
	assert(is_sorted(all(orig)));
	sort(all(rem));
	int p = 0;
	vector<int> l;
	for(int i = 0; i<sz(orig); i++){
		while(p < sz(rem) && rem[p] < orig[i]){
			p++;
		}
		if(p >= sz(rem) || rem[p] != orig[i]) l.pb(orig[i]);
	}
	return convexHull(l);
}

void print(vector<int> a, string b){
	cout << b << " ring:\n";
	for(int x : a){
		cout << x << " ";
	}
	cout << endl;
}


int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	for(int i = 0; i<n; i++){
		ll x, y;
		cin >> x >> y;
		arr.pb(P(x, y));
	}
	vector<int> allp(n), fring, sring, tring, allring;
	//allring will end up storing the elemens of all three rings
	iota(all(allp), 0); //just a list of elements [0, n)
  fring = removed_ch(allp, {});  //first ring
	allring.insert(allring.end(), all(fring)); 
	sring = removed_ch(allp, allring); //second ring
	allring.insert(allring.end(), all(sring));
	tring = removed_ch(allp, allring); //third ring
	allring.insert(allring.end(), all(tring));
	//pretty cancer :notlikeduck:
	
	map<pii, ll> m; //(a, b), ch without a and b
	m.insert(mp(mp(n, n), pA2(fring))); //ch of the entire array
	

	sort(all(fring)); //i need to binsearch for queries
	sort(all(sring)); 
	sort(all(allring));
	for(int x : fring){
		m.insert(mp(mp(x, n), pA2(removed_ch(allring, {x}))));
		//area with only 1 point on the first ring removed
	}
	
	for(int x : fring){
		for(int y : fring){
			if(y == x) continue;
			ll ans = pA2(removed_ch(allring, {x, y}));
			m.insert(mp(mp(x, y), ans));
			m.insert(mp(mp(y, x), ans));
		}
		for(int y : sring){
			ll ans = pA2(removed_ch(allring, {x, y}));
			m.insert(mp(mp(x, y), ans));
			m.insert(mp(mp(y, x), ans));
		}
	}
	while(q--){
		int a, b;
		cin >> a >> b;
		a--, b--; //0 based
		int c = binary_search(all(fring), a), d = binary_search(all(fring), b);
		if(d){ swap(a, b); swap(c, d); } //never have b on fring and a not
		if(!c && !d){
			//neither is on the first ring
			cout << m[mp(n, n)] << "\n";
		}else{
			int e = binary_search(all(sring), b);
			if(c && (d || e)){ 
				//a is on the first ring and b is on the first/second ring
				cout << m[mp(a, b)] << "\n";
			}else{
				//a is on the first ring and b is further in
				cout << m[mp(a, n)] << "\n"; 
			}	
		}
		
	}

	return 0;
}


