# Chessbot's Lawn

## statement
Chessbot owns a lawn which has $N$x$M$ $(1 \leq N, M \leq 1000)$ patches of grass, represented as a grid of squares, where the top left square is labeled $(1, 1)$ and the bottom right one is labeled $(N, M)$. Each patch of grass has a beauty value $b_{ij}$ associated with it, which denotes the beauty value for the square in the $i$th row and $j$th column $(1 \leq i \leq N, 1 \leq j \leq M)$. Because Chessbot is a negative person, he only cares about the least beauty value. He would like to survey parts of his lawn from the top left square $(1, 1)$ to a square $(x, y)$ to see what the minimum beauty value is of that part of his lawn.

## input format
The first line contains $N$, $M$, and $Q$ $(1 \leq Q \leq 1000)$, where $Q$ denotes the number of queries Chessbot will ask about his lawn.

The next $N$ lines will contain an $N$x$M$ matrix of integers $b_{ij}$ $(1 \leq b_{ij} \leq 10^9)$.

The final $Q$ lines will contain two integers $x_q$ and $y_q$.

## output format

For each query, output the minimum beauty value of the portion of the grid from $(1, 1)$ to $(x_q, y_q)$.

## sample input
```
4 5 3
2 3 1 6 2
3 2 1 5 3
5 6 2 3 1
9 6 3 7 2
4 2
1 3
4 3
```

## sample output
```
2
1
1
```

## sample explanation
In the first query, the part of the lawn that Chessbot is interested in is

2 3

3 2

5 6

9 6

The minimum beauty value in this section is $2$.

## notes
Problem idea: Bossologist

Problem preparation: Bossologist

TL: 2 seconds

ML: 256mb

Occurances: Novice 11, Intermediate 4
