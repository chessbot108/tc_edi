# Cooked Fish (Hard Version)

## statement

This is the revised version since i am too lazy to fix the checker.

This is the hard version of the problem. The difference between the easy and hard versions is that for this problem (the hard version) $ (2 \leq k \leq 20 ) $ and $ (1 \leq n \leq 10^{18}) $.

Peach has finally taken Goma out to eat fried fish. There is an infinite amount of fish in the restaurant they are at. They are lined up in a way such that the $i$th fish from the entrance has flavor $i^k$. In other words, the fishes have flavor $1^k, 2^k, 3^k, 4^k, \cdots, \infty^k$. So when eating, Peach will pick a starting point and an ending point and eat all the fishes from the starting point to the ending point (excluding the ending point). The total flavor of those fishes will be the sum of the flavor of each individual fish, so if the starting point is $4$ and the ending point is $6$ (with $k = 1$), the total flavor is 9 (excluding endpoint), if $k$ was equal to $3$, it would be $4^3 + 5^3$ or $189$. They will visit the restaurant for the next $Q$ days would like to eat a total flavor of $n[i]$ on day $i$ and would like you to find any pair of starting and ending points such that the total flavor is $n[i]$. Due to the fact they do not want to walk that far before eating, the ending point must be $\leq n$.

More formally, you will have to answer $D$ queries with each query being two numbers $n$ and $k$ and you have to find and output any two numbers $a$ and $b  (1 \leq a < b \leq n) $ such that $\sum_{i=a}^{b-1} i^k $. Remember again to exclude the right endpoint.

## input description

The first line will be one integer $Q$, the number of queries $(1 \leq Q \leq 10)$ followed by $Q$ lines of $2$ integers on the $i$th line, $n[i]$ $(1 \leq n \leq 10^{18})$ the total flavor of fish they want to eat on the $i$th day and $k[i]$ $(2 \leq k \leq 20)$, the $k$ used to evaluate flavors on the $i$th day.

## output description

$D$ lines with two integers the i'th line, $a[i]$ and $b[i]$ $(1 \leq a[i] < b[i] \leq n)$ where $\sum_{i=a}^{b-1} i^k $ is equal to $n[i]$. If there is no $a$ and $b$ that satisfy the constraints, output "-1 -1" without the quotes. If there are multiple solutions, output the one that minimizes $a$.

If your answer does not satisfy $(1 \leq a < b \leq n)$, $\sum_{i=a}^{b-1} i^k $ is not equal to $n$, or you did not find an answer for a pair the judger determines there is an answer to, you will receive WA as your verdict.

## sample input

```
4
4 2
6 3
189 3
54 2
```

## sample output

```
2 3
-1 -1
4 6
2 6
```

## sample explanation

For $n = 4$ and $k = 2$, $(2, 3)$ is the only solution $2^2 = 4$. 

For $n = 6$ and $k = 3$, it can be shown that there is no solution. 

The fourth testcase was described in the problem statement.

For $n = 54$ and $k = 2$, the solution is $(2, 6)$, $2^2 + 3^2 + 4^4 + 5^2 = 4 + 9 + 16 + 25 = 54$.

## notes
Problem idea: chessbot/codicon/PurpleCrayon
Problem preparation: chessbot
TL: 2 seconds
ML: 256 MB
Occurances: Intermediate 11, Advanced 6
