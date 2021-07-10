
#include <stdio.h>
#include <cassert>
#define AC 0
#define WA 1
#define ERROR -1
#define ll long long
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int MX = 2e6+10;

ll arr[MX];

int k_1(ll n, ll k){
	// if x is a power of 2, the only solution is for a == b == x
	// idea is (b-a+1)*(b+a) = 2*x you can find the divisors by noting one must be even and the other odd
	
	ll y = (n&(-n))*2; // even divisor = 2 * largest power of 2 that divides x
	ll z = n/(y/2); // odd divisor = x / largest power of 2 that divides it
	
	ll a = (abs(z-y)+1)/2; // 2*a-1 = difference between divisors
	ll b = max(z,y)-a; // largest divisor = b+a
	if(n&(n-1)) return 1; //dark magic saying n is not a power of 2
	else return 0;
}


__int128 sq(__int128 a){
	//sqrt of a
	__int128 ans = 0;
	for(__int128 i = 63; ~i; i--){
		__int128 p = ((__int128)1 << i);
		if((p + ans) * (p + ans) <= a) ans += p;
	}
	return ans;
}

int k_2(ll n, ll k){ //for when k = 2
	__int128 s1 = 0, s2 = 0; //sum of integers and sum of squares
	ll a = -1, b = -1;
	for(__int128 i = 1; s2 <= n; i++){
		
		__int128 disc = (2ll * s1)*(2ll * s1) - (4ll * i * (s2 - n));
		__int128 tmp = sq(disc);
		__int128 A = (-(2ll * s1) + tmp);
		//quadratic formula yayy
		if(!(tmp*tmp != disc || A%(i * 2ll) != 0)){
			a = A/(i * 2ll);
			b = a + i;
			break;
			
		}
		s1 += i;
		s2 += i*i;
	}
	if(a == 0) a++;
	if(a == -1 && b == -1) return 0;
	else return 1;
}

ll Pow(ll a, ll k, ll n){
	if(a == 0) return 0;
	ll ans = 1;
	for(int i = 0; i<k; i++){
		if(n/ans < a) return -1;
		ans *= a;
	}
	return ans;
}

int k_3(ll n, ll k){ //for all cases k >= 3
	int R = 0;
	for(int i = 0; Pow(i, k, n) >= 0; i++){
		arr[R++] = Pow(i, k, n);
	}
	
	ll l = 0, r = 0, tot = 0;

	for(int i = 0; i<R; i++){ //am *i* a joke to you
		while(r+1 < R && tot + arr[r+1] <= n){
			r++;
			tot += arr[r];
		}
		if(tot == n) break;
		tot -= arr[l];
		l++;
	}
	if(l == 0) l++;
	//found sol/no sol
	if(tot != n) return 0;
	else return 1;
}


int spj(FILE *input, FILE *user_output){
    /*
      parameter: 
        - input, pointer of the input file
        - user_output, pointer of user's output
      return: 
        - If answer is correct, return AC
        - If answer is wrong, return WA
        - If an error is caught, return ERROR
     */
     // Do judging here
		
		//if:
		//1. !(1 <= a < b <= 1e5), WA
		//2. sigma [a, b) is not X, WA
		int T, flag = AC;
		fscanf(input, "%d", &T);
		for(int t = 0; t<T; t++){
			int n, a, b, k;
			if(fscanf(input, "%d%d", &n, &k) == -1){ 
				flag = ERROR;
			}
			if(fscanf(user_output, "%d%d", &a, &b) == -1){
				flag = ERROR;
			}
			if(~flag){
				break;
			}
			int jud, val = 0;
			if(k == 1) jud = k_1(n, k);
			else if(k == 2) jud = k_2(n, k);
			else jud = k_3(n, k);

			if(k == 1){
				if(1 <= a && a < b && b <= n){
					__int128 sum = 0;
					sum = (b - a) * (b + a - 1) /2ll;
					if(sum == n){
						val = 1;
						assert(jud);
					}
				}else{
					if(a == -1 && b == -1 && !jud) val = 1;
				}
			}else{
				if(1 <= a && a < b && b <= n){
					__int128 tot = 0;
					for(ll i = a; i<b; i++) tot += (__int128)i;
					if(tot == n){
						val = 1;
						assert(jud);
					}
				}else{
					if(a == -1 && b == -1 && !jud) val = 1;
				}
			}
			if(!val) flag = WA;
		}		
		return flag;
}

void close_file(FILE *f){
    if(f != NULL){
        fclose(f);
    }
}

int main(int argc, char *args[]){
    FILE *input = NULL, *user_output = NULL;
    int result;
    if(argc != 3){
        printf("Usage: spj x.in x.out\n");
        return ERROR;
    }
    input = fopen(args[1], "r");
    user_output = fopen(args[2], "r");
    if(input == NULL || user_output == NULL){
        printf("Failed to open output file\n");
        close_file(input);
        close_file(user_output);
        return ERROR;
    }

    result = spj(input, user_output);
    printf("result: %d\n", result);
    
    close_file(input);
    close_file(user_output);
    return result;
}

