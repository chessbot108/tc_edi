# Cooked Fish (Easy Version) Editorial

So lets say $(a, b)$ is a valid answer. Let's define $n$ as $\sum_{i =a}^{b-1} i$ and try to rewrite $n$. 
$$
n = \sum_{i = a}^{b - 1} i = \sum_{i = 0}^{(b - a) - 1} a + i = (b - a - 1) \cdot a + \sum_{i = 0}^{b - a - 1} i = (b - a) * a + (\frac{(b - a - 1) \cdot (b - a)}{2})
$$
So i started out with the definition of $n$, then I subtracted $a$ from all $i$, then i removed $a$ from the sigma since it's independant, then finally I simplified the sum of the first $b - a$ nonnegative integers with gauss's. So now, if $(a, b)$ is a valid solution, we can express $a$ in terms of $n$ and $b - a - 1$. Let's define $k$ as $(b - a)$ (note this is different from $k$ in the problem statement). We have
$$
n = k * a + \frac{k \cdot (k -1)}{2}.
$$
If we set $a = 0$, once $k$ grows large enough, it's side of the equation will be greater than $n$. namely when $k$ is around $\sqrt{2} \cdot n$, $\frac{k \cdot (k - 1)}{2}$ will be around the size of $n$. So as result there are only around $O(\sqrt{n})$ values for k that are suitable. So now let's rewrite our equation.
$$
\frac{n - {\frac{k \cdot (k - 1)}{2}}}{k} = a
$$
 So since since we know that $a$ is an integer, $(n - \frac{k \cdot (k - 1)}{2})$ must be divisible by $k$ for $a$ to end up as an integer. So if we have $a$, $b = a + k$. So we can check all $O(\sqrt{n})$ values of $k$ and check if there is a solution. Also note by some math magic, there is no solution for the problem when $n$ is a power of $2$. The end complexity is $O(\sqrt{n})$.

The code is below

```cpp
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;
const int MX = sqrt(2e9) +10; //around 45000
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int T; cin >> T;
	while(T--){
		int X, temp; cin >> X >> temp; //X = n, temp = k (temp == 1)
		assert(temp == 1);
		int a = -1, b = -1, found = 0; 
		for(int k = 1; k<=MX; k++){ //for all X, the length no exceed sqrt(2*X), or sqrt(2e9)
			int s = ((k * (k - 1))/2);
			if(s > X) break; //sanity check
			if((X - s)%k == 0){
				a = (X - s)/k, b = a + k; 
			}
		}
		
		if(a == 0){
			a++; //just an edge case, starting from 0 and starting at 1 are the same
		}
		if(X&(X-1)) cout << a << " " << b << "\n";	//fancy way of checking if a number is not a power of 2
		else cout << "-1 -1\n";
	}

	return 0;
}
```



Bonus: prove that there is no solution for when $n$ is a power of $2$, also trying solving this for $n \leq 10^{18}, k =1$.
