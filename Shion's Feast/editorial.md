We want the lcm to be as large as possible. The lcm is large if we have two large numbers that are relatively prime since their lcm is their product. Motivated by this, we ask: is there a large number we can add that will be relatively prime to the maximum number in the array? 

Let $MX$ be the maximum number in the array. Realize that $MX$ and $K \cdot MX-1$ are relatively prime ($gcd(MX, \, K \cdot MX -1) = 1$) using the Euclidean algorithm. Here's an intuitive (and equivalent) proof. Let $d$ be a divisor of $MX$, then $d$ also divides $K \cdot MX$. Thus, the only way that $d$ would divide $K \cdot MX-1$ is if it divides $-1$, so $d$ must be $1$ if it does). 

Therefore, we add $B = K \cdot MX-1$ if $MX$ is not $1$ otherwise we add $B = K \cdot MX$. 



Time complexity: $O(N)$


