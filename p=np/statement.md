# P=NP

## statement

PurpleCrayon has recently solved P=NP! He refused to share his proof (or his $\$1000000$ prize as part of the raffle prize pool) so we cannot use it as our Very Easy 1. Instead, we decided to create our own P=NP, so here it is. Count the number of solutions to the equation

$P=N \cdot P$ 

when $0 \leq P \leq X$ and $0 \leq N \leq Y$ where $X$ and $Y$ are given as input.

## input format
One line with two integers, $X$ and $Y$. ($1 \leq X, Y \leq 1000$). Note that despite $X$ and $Y$ being greater than $0$, $N$ and $P$ in the equation can be greater than or equal to $0$.

## output format

A single integer denoting the number of pairs $(N, P)$ such that $P=N \cdot P$ and $(0 \leq N \leq X)$ and $(0 \leq P \leq Y)$.

## sample input
```
2 2
```

## sample output
```
5
```

## sample explanation
The valid pairs of $(N, P)$ are $(0, 0)$, $(1, 0)$, $(1, 1)$, $(1, 2)$, and $(2, 0)$.

## notes
Problem idea: chessbot

Problem preparation: chessbot

TL: 2 seconds

ML: 256mb

Occurances: Novice 1, Intermediate 1
