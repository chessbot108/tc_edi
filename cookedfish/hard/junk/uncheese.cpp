//submission by mike4235 fanclub

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
//#include <random>
#include <chrono>
#include <queue>
#include <set>

using namespace std;
//using namespace __gnu_pbds;

#define endl '\n'
#define fi first
#define se second
#define For(i, l, r) for (int i = l; i < r; i++)
#define ForE(i, l, r) for (int i = l; i <= r; i++)
#define FordE(i, l, r) for (int i = l; i >= r; i--)
#define Fora(v, a) for (auto v: a)
#define bend(a) a.begin(), a.end()
#define isz(a) ((signed)a.size())
#define ull __int128
using ll = long long;
using ld = long double;
using pii = pair <int, int>;
using vi = vector <int>;
using vpii = vector <pii>;
using vvi = vector <vi>;

const int N = 4e5 + 5;

// correctness proved in https://github.com/kth-competitive-programming/kactl/blob/master/doc/modmul-proof.pdf
// twice faster than (__int128_t)a * b % M
//typedef unsigned long long ull;
ull mod_mul(ull a, ull b, ull M){
    long long res = a * b - M * ull(1.L / M * a * b);
    return res + M * (res < 0) - M * (res >= (long long)M);
}
ull mod_pow(ull b, ull e, ull mod){
    ull res = 1;
    for(; e; b = mod_mul(b, b, mod), e >>= 1) if(e & 1) res = mod_mul(res, b, mod);
    return res;
}
// Millar Rabin Primality Test
// 7 times slower than a^b mod c
bool isprime(ull n){
    if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull s = __builtin_ctzll(n - 1), d = n >> s;
    for(ull a: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
        ull p = mod_pow(a, d, n), i = s;
        while(p != 1 && p != n - 1 && a % n && i --) p = mod_mul(p, p, n);
        if(p != n - 1 && i != s) return false;
    }
    return true;
}
// Pollard rho algorithm
// O(n^1/4)
ull get_factor(ull n){
    auto f = [n](ull x){ return mod_mul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while(t ++ % 40 || __gcd(prd, n) == 1){
        if(x == y) x = ++ i, y = f(x);
        if(q = mod_mul(prd, max(x, y) - min(x, y), n)) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}
vector<ull> __factorize(ull n){ // returns the prime factors in arbitrary order
    if(n == 1) return {};
    if(isprime(n)) return {n};
    ull x = get_factor(n);
    auto l = __factorize(x), r = __factorize(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

ull binpow(ull x, int y){
    ull ans = 1;
    while (y){
        if (y & 1) ans *= x;
        x *= x;
        y >>= 1;
    }
    return ans;
}

vector <ull> factorize(ull n){
    vector <ull> ans;
    if (n <= 4e12){
        for (int i = 1; (ull)i * i <= n; i++){
            if (n % i){
                continue;
            }
            ans.emplace_back(i);
        }
        return ans;
    }
    For(i, 1, 2000000){
        if (n % i){
            continue;
        }
        ans.emplace_back(i);
    }
    vector <ull> tmp = __factorize(n);
    Fora(&i, tmp){
        if (i <= 2000000){
            continue;
        }
        if (i <= n / i){
            ans.emplace_back(i);
        }
    }
    return ans;
}

ull n; int k;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("KEK.inp", "r", stdin);
    // freopen("KEK.out", "w", stdout);
int q; cin >> q; while (q--){
	  ll x ;
    cin >> x >> k;
		n = x;
    if (k == 1){
        n *= 2;
        bool ck = 0;
        vector <ull> divisors = factorize(n);
        Fora(&i, divisors){
            if (i > n / i or i == 1){
                continue;
            }
            if (i % 2 == n / i % 2){
                continue;
            }
            ull l = (n / i - i + 1) / 2, r = n / i + 1 - l;
            cout << (ll)l << ' ' << (ll)r << endl;
            ck = 1;
            break;
        }
        if (!ck){
            cout << -1 << ' ' << -1 << endl;
        }
    }
    else if (k == 2){
        n *= 6;
        bool ck = 0;
        vector <ull> divisors = factorize(n);
        Fora(&i, divisors){
            if (i >= n / i){
                continue;
            }
            if (2 * i * i - 3 * i + 1 < n / i){
                ll a = 6, b = 6 * i - 6, c = 2 * i * i - 3 * i + 1 - n / i;
                if (b % a or c % a){
                    continue;
                }
                ull det = b * b - 4 * a * c;
                if (det < 0 or det % (a * a)){
                    continue;
                }
                ull m = round(sqrtl(det / a / a));
                if (m * m * a * a != det){
                    continue;
                }
                if (m % 2 != b / a % 2){
                    continue;
                }
                ull l1 = (-b + a * m) / (2 * a), l2 = (-b - a * m) / (2 * a);
                if (l1 >= 1){
                    ull r = l1 + i;
                    cout << (ll)l1 << ' ' << (ll)r << endl;
                    ck = 1;
                    break;
                }
                if (l2 >= 1){
                    ull r = l2 + i;
                    cout << (ll)l2 << ' ' << (ll)r << endl;
                    ck = 1;
                    break;
                }
                continue;
            }
            ull a = 6, b = 6 * i - 6, c = 2 * i * i - 3 * i + 1 - n / i;
            if (b % a or c % a){
                continue;
            }
            ull det = b * b - 4 * a * c;
            if (det < 0 or det % (a * a)){
                continue;
            }
            ull m = round(sqrtl(det / a / a));
            if (m * m * a * a != det){
                continue;
            }
            if (m % 2 != b / a % 2){
                continue;
            }
            ull l1 = (-b + a * m) / (2 * a), l2 = (-b - a * m) / (2 * a);
            if (l1 >= 1){
                ull r = l1 + i;
                cout << (ll)l1 << ' ' << (ll)r << endl;
                ck = 1;
                break;
            }
            if (l2 >= 1){
                ull r = l2 + i;
                cout << (ll)l2 << ' ' << (ll)r << endl;
                ck = 1;
                break;
            }
        }
        if (!ck){
            cout << -1 << ' ' << -1 << endl;
        }
    }
    else{
        ld ldlim = powl(n, 1.0 / k); int lim = ldlim;
        if (fabs(ldlim - round(ldlim)) < 1e-9){
            lim = round(ldlim);
        }
        vector <__int128_t> a;
        __int128_t sum = 0;
        a.emplace_back(sum);
        bool ck = 0;
        ForE(i, 1, lim){
            sum += binpow(i, k);
            if ((*lower_bound(bend(a), sum - n)) == sum - n){
                cout << lower_bound(bend(a), sum - n) - a.begin() + 1 << ' ' << i + 1 << endl;
                ck = 1;
                break;
            }
            a.emplace_back(sum);
        }
        if (!ck){
            cout << -1 << ' ' << -1 << endl;
        }
    }
}
}

