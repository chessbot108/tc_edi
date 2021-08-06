
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
#include <set>
#include <random>
#include <chrono>
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
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

char inp[20];

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
	int n, q, d, t, s;
	int p1, p2, p3, p4;
	
	cin >> t >> s >> n >> q >> d;
	cin >> p1 >> p2 >> p3 >> p4; 	
	
	mt19937_64 rng(s);
	sprintf(inp, "%d.in", t);
	freopen(inp, "w", stdout);
	cout << n << " " << q << "\n"; //5e5
	set<pair<int, int>> vis;
	for(int i = 0; i<n; i++){
		int a = uid(1, d), b = uid(1, d);
		while(vis.count(make_pair(a, b))){
			a = uid(1, d), b = uid(1, d);
		}
		arr.pb(P(a, b));
		cout << a << " " << b << "\n";
	}
	vector<int> allp(n), fring, sring, tring, allring;
	//allring will end up storing the elemens of all three rings
	iota(all(allp), 0); //just a list of elements [0, n)
  fring = removed_ch(allp, {});  //first ring
	allring.insert(allring.end(), all(fring)); 
	sring = removed_ch(allp, allring); //second ring
	for(int i = 0; i<q; i++){
		int a = uid(0, p1+p2), b = uid(0, p3 +p4);
		int x, y;
		if(a < p1){
			int t = uid(0, sz(fring)-1);
			x = fring[t];
		}else{
			x = uid(0, n-1);
		}

		if(b < p3){
			int t = uid(0, sz(sring)-1);
			y = sring[t];
		}else{
			y = uid(0, n-1);
		}
		if(x == y){
			if(x == n-1) x--;
			else x++;
		}
		cout << x+1 << " " << y+1 << "\n";
	}
	return 0;
}


