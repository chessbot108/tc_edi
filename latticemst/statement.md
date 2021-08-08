# Lattice MST

## statement

Chessbot had a problem of finding the maximum spanning tree, but since he was too lazy to generate graphs, so he proposed to just use an $ N $ x $ M$ lattice where the distance between two points was the euclidian distance squared. PurpleCrayon decided this problem wasn’t hard enough and decided to make it a d-dimensional lattice grid where the distance between two points $ p_{1} $ and $ p_{2} $, where each point is represented as a tuple length $ d $ , $ x_{1}, x_{2}, \cdots, x_{d} $ where $x_i$is the location on the $i$th dimension, is $ \sum_{i=1}^d | p_{1,i} - p_{2,i} |^k $, where $d$ and $k$ are given as input. So the question is given a d-dimensional lattice grid (with the i'th dimension being D[i]) and k, find the maximum spanning tree of the graph where there is an edge between all points from $ (1, 1, \cdots, 1)$ and $(D[1], D[2], \cdots, D[d])$ of the lattice equivalent to the distance formula described above. 



## input format

You will answer $ T $ testcases $ (1 \leq T \leq 10) $. Each testcase consists of 2 lines. The first line is two integers $ d (2 \leq d \leq 60) $ and $ k (1 \leq k \leq 500)$. The following line consists of $d$ integers, which describes the dimensions of the $d$-dimensional lattice $ (D[i] \leq 10^9) $.

Testcase 2 satisfies, $ d = k = 5, (1 \leq D[i] \leq 5) $.



## output format

The one integer for the $i$th testcase, $ans[i]$, which is the maximum spanning tree of the lattice grid inputted. Since this number may be very large, please find it modulus $10^9 +7$.



## sample intput

```
3
2 2 
2 2
3 2 
2 2 2
4 20
6 9 96 66
```

## sample output

```
5
18
742488253
```



## sample explanation

For the first testcase, you could draw edges between: $ (1, 1) $ and $ (2, 2) $ with weight $ |1 - 2|^2 + |1 - 2|^2 $, $(1, 2)$ and $(2, 1)$ with weight $|1 - 2|^2 + |2 - 1|^2$ , $(1, 1)$ and $(2, 1)$ with weight $|1 - 2|^2 + |1 - 1|^2$ or $2 + 2 + 1$ summing up to $5$.

For the second testcase, edges are between $(1, 1, 1) \rightarrow (2, 2, 2)$; $(1, 1, 1) \rightarrow (2, 2, 1)$, $(1, 1, 1) \rightarrow (2, 1, 2)$, $(1, 1, 1) \rightarrow (1, 2, 2)$, $(1, 2, 1) \rightarrow (2, 1, 2)$, $(2, 1, 1) \rightarrow (1, 2, 2)$, $(1, 1, 2) \rightarrow (2, 2, 1)$ with a total sum of $4*(1^2 + 1^2 + 1^2)$ + $3*(1^2 + 1^2 + 0^2)$.

Due to the difficulty of drawing a $6\times9\times96 \times 66$ $4$-dimension lattice grid on a $2$d screen, an explanation is omitted.

## notes

Problem idea: chessbot/PurpleCrayon

Problem preparation: chessbot

TL: 2 seconds

ML: 256mb

Occurances: Advanced 15
