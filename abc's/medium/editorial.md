We will solve the problem using dp. Let $dp(i, k)$ be the answer when $i$ is the amount of turns, and $k$ is the last letter played. So find this value we have two cases.

Case 1: $i \neq N$
We have $dp(i, k) = max(dp(j, k) + pre(i, k) - pre(j, k))$, where $k < j \leq i-k$ and $pre(a, k)$ is the amount of points the player will get if you played card a for the first $k$ turns

Case 2: $i = N$
We have $dp(i, k) = max(dp(j, k) + pre(i, k) - pre(j, k))$, but this time $k < j \leq i$ because at the end there doesn't need to be $K$ cards of the same type.

To do this in linear time, we precompute $pre(i, j)$ and maintain an array $val$ where $val[m]$ is computed as $max(dp(i, m)) - pre(j, k))$ for each $k$ where $m$ is, and have
$dp(i, k) = val[j] + pre(i, k)$

With this adjustment, it is solvable in linear time.
