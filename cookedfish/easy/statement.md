# Cooked Fish (Easy Version)

## statement
This is the easy version of the problem. The difference between the easy and hard versions is that for this problem (the easy version) $k = 1$ and $(1 \leq n \leq 10^{9})$.

Peach has finally taken Goma out to eat fried fish. There is an infinite amount of fish in the restaurant they are at. They are lined up in a way such that the $i$th fish from the entrance has flavor $i^k$. In other words, the fishes have flavor $1^k, 2^k, 3^k, 4^k, \cdots, \infty^k$. So when eating, Peach will pick a starting point and an ending point and eat all the fishes from the starting point to the ending point (excluding the ending point). The total flavor of those fishes will be the sum of the flavor of each individual fish, so if the starting point is $4$ and the ending point is $6$ (with $k = 1$), the total flavor is $9$ (excluding endpoint). They will visit the restaurant for the next $D$ days would like to eat a total flavor of $n[i]$ on day $i$ and would like you to find any pair of starting and ending points such that the total flavor is $n[i]$. Due to the fact they do not want to walk that far before eating, the ending point must be $\leq n$.

More formally, you will have to answer D queries with each query being two numbers $n$ and $k$ $(k = 1)$, and you have to find and output any two numbers $a$ and $b  (1 \leq a < b \leq n)$ such that $\sum_{i=a}^{b-1} i^k $ is $n$. Remember again to exclude the right endpoint.

## input format
The first line will be one integer $D$, the number of days $(1 \leq D \leq 10)$ followed by $D$ lines of 2 integers on the $i$th line, $n[i]$ $(1 \leq n \leq 10^{9})$ the total flavor of fish they want to eat on the $i$th day and $k[i]$, the $k$ used to evaluate flavors on the $i$th day. Remember for this version of the problem, $k = 1$ for all testcases.

## output format
$D$ lines with two integers the $i$th line, $a[i]$ and $b[i]$ $(1 \leq a[i] < b[i] \leq n)$ where $\sum_{i=a}^{b-1} i^k $ is equal to $n[i]$. If there is no $a$ and $b$ that satisfy the constraints, output "-1 -1" without the quotes. If there are multiple solutions, output any of them.

If your answer does not satisfy $(1 \leq a < b \leq n)$, the $\sum_{i=a}^{b-1} i^k $ is not equal to $n$, or you did not find an answer for a pair the judger determines there is an answer to, you will receive WA as your verdict.

## sample input
```
4
1 1
4 1
6 1
54 1
```

## sample output
```
-1 -1
-1 -1
1 4
2 11
```

## sample explanation
Remember $k = 1$ for all testcases.

There is no solution for $n = 1$. $(1, 2)$ is not a valid solution since $2$, the ending point, is larger than $n$, or $(1 \leq 1 < 2 \leq n)$ is not satisfied.

There is also no solution for $n = 4$.

For $n = 6$, $(1, 4)$ is the only solution, not $(6, 7)$ does not work since $7$ is not $\leq 6$, or $7$ is not $\leq n$. Also just note that $(5, 6)$ does not work since this sums up to $5$, not $6$.

For $n = 54$, $(2, 11)$, $(12, 16)$ and $(17, 20)$ are all solutions.

## notes
Problem idea: chessbot

Problem preparation: chessbot

TL: 2 seconds

ML: 256mb

Occurances: Novice 12, Intermediate 7, Advanced 2
