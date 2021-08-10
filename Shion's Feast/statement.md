# Shion's Feast

## statement

Shion is cooking an amazing feast for you—so amazing that her toxic food sometimes melts through the bowl! She uses $N$ $(1 \leq N \leq 10^5)$ ingredients where the quantity of the $i$th ingredient is $A_i$ $(1 \leq A_i \leq 10^5)$. The tastiness of the meal is the maximum of $lcm(A_i, A_j)$ over all $i < j$. You don’t want to acquire the poison resistance skill after eating her food, so you decide to sneak in an extra ingredient with quantity $B$ $(1 \leq B \leq K \cdot max(A_i), \, 2 \leq K \leq 10)$ for Shion to also use. Find the value of $B$ that maximizes the tastiness of your potentially final feast!

## Input format

The first line contains one integer, $T$ $(1 \leq T \leq 10^4)$, the number of test cases. Then $T$ test cases follow.

The first line of each test case contains two integers, $N, K$.

The second line of each test case contains $N$ integers, $A_1, A_2, \dots , A_N$.

It is guaranteed that the sum of $N$ over all test cases does not exceed $10^5$.

## Output format

For each test case, output the value of $B$ that maximizes the tastiness of your feast.

## sample input
```
2
3 2
1 1 1
3 2
1 1 2
```

## sample output
```
2
3
```

## sample explanation

For the first test case, $B$ can be $1$ or $2$. $B=2$ gives tastiness $ = \max(lcm(1,1), \, lcm(1,1), \, lcm(1,1), \, lcm(1,2), \, lcm(1,2), \, lcm(1,2)) = 2$, which is the maximum, so $2$ is the answer.


For the second test case, $B$ can be $1, \, 2, \, 3,$ or $4$. $B=3$ gives tastiness $ = \max(lcm(1,1), lcm(1,2), lcm(1,2), lcm(1,3), lcm(1,3) ,lcm(2,3)) = 6 $, which is the maximum, so $3$ is the answer.

## notes
Problem idea: codicon

Problem preparation: codicon

TL: 2 seconds

ML: 256mb

Occurances: Novice 13, Intermediate 8, Advanced 3 
