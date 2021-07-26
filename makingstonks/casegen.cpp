#include <bits/stdc++.h>

using namespace std;

inline int random(int l, int r, mt19937& rng) { return uniform_int_distribution<int>(l, r)(rng); }

signed main(signed argc, char* argv[]){
    freopen("10.in", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(atoi(argv[1]));

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int n = random(90000, 100000, rng), x = random(1, 1000000, rng);

    printf("%d %d\n", n, x);

    for (int i = 0; i < n; ++i) {
        int t = random(1, 1000000000, rng), r = random(1, 1000, rng);
        printf("%d %d\n", t, r);
    }


    return 0;
}