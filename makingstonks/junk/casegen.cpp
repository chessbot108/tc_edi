#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

inline ll random(ll l, ll r, mt19937_64& rng) { return uniform_int_distribution<ll>(l, r)(rng); }

signed main(signed argc, char* argv[]){
    for (int cs = 4; cs <= 10; ++cs) {
        freopen((to_string(cs) + ".in").c_str(), "w", stdout);
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        srand(atoi(argv[1]));

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

        int n = random(90000, 100000, rng);
        ll x = random((ll)1e11, (ll)1e12, rng);

        printf("%d %lld\n", n, x);

        for (int i = 0; i < n; ++i) {
            int t = random(1, 1000000000, rng), r = random(1, 1000, rng);
            printf("%d %d\n", t, r);
        }
    }


    return 0;
}