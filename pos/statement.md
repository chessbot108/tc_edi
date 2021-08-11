# Position of Set

## statement
Teamscode has created a problem set for the constants to solve. A problem set consists of $N$ different problems with each problem having a difficulty $d$ (not necessarily distinct) and the difficulty is nondecreasing from $1$ to $N$. However, the day before the contest, Bossologist messed up and scrambled the problem set into a random order. The rest of the problem writing team is now angry at Bossologist, and would like to compute the number of possible original problem sets to make a case to HR.

## input format
The first line contains $N$ $(1 \leq N \leq 10^6)$.

The next $N$ lines contain a unique string $s$ and an integer $d$, where $s$ is the problem name, and $d$ is the problem difficulty. $(1 \leq d \leq 10^6)$ The sum of the lengths of all strings is guaranteed less than or equal to $10^7$.

## output format
Output the number of possible different original problem sets, given that a problem set has problem difficulties in a non-decreasing order, and considered distinct if a problem $p$ appears in a different spot for any $p$. Due to the large number of possible original problem sets, please output the answer mod $10^9 + 7$.

## sample input
```
9
Average 1 
Premins 9 
Costs 2 
Ordering 3 
Books 3 
ABCs 2 
Multiples 5 
Teleport 2 
P=NP 9
```

## sample output
```
24
```

## sample explanation
The answer is not 12...
One possible original problem set is:

Average, Costs, ABCs, Teleport, Ordering, Books, Multiples, P=NP, and Premins in that order.

Another one is:

Average, ABCs, Costs, Teleport, Ordering, Books, Multiples, Premins, and P=NP.

## notes
Problem idea: Bossologist

Problem preparation: Bossologist

TL: 2 seconds

ML: 256mb

Occurances: Novice 8, Intermediate 5
