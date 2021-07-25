#include <stdio.h>
#include <cassert>
#define AC 0
#define WA 1
#define ERROR -1
#define ll long long
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
			int X = -1, a = -1, b = -1, k;
			
			fscanf(input, "%d%d", &X, &k);
			assert(k == 1);
			fscanf(user_output, "%d%d", &a, &b);
			if(X&(X-1)){ //X is not a power of two, there should be a sol
				if(!(1 <= a && (a < b) && (b <= (int)X))) flag = WA;
				ll ans = 0;
				for(int i = a; i<b && ans <= X; i++){
					ans += (ll)i;
				}
				if(ans != (ll)X) flag = WA;
			}else{
				if(a != -1 || b != -1) flag = WA;
			}		
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
