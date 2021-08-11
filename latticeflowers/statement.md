# Lattice Flowers

## statement
Goma was busy picking flowers for Peach when he discovered a patch of flowers in the form of an $N$x$M$ lattice with one flower per point. Starting from point $(1, 1)$ of the lattice, Goma will walk in a straight line picking up all flowers in the points he passes through (including $(1, 1)$). He wants to find a path to maximize the number of flowers he picks, and he also wants to know the number of ways to walk that will maximize the number of flowers he picks up.

## input format
You will answer $T$ testcases $(1 \leq T \leq 10)$ where each testcase is: two integers $N$, $M$ $(2 \leq N, M \leq 1000)$, the dimensions of the grid.

The first line of the input will be $T$, followed by $T$ lines with two integers each $N$ and $M$ respectively.

## output format
Two integers $a$ and $b$ where $a$ is the maximum amount of flowers that can be picked up by Goma starting from $(1, 1)$ and $b$ is the number of unique ways he can walk to pick up flowers starting from point $(1, 1)$.

## sample input
```
2
2 2
3 2
```

## sample output
```
2 3
3 1
```

## sample explanation

In the first testcase, Goma can pick up two flowers at most, and he can walk from $(1, 1)$ to $(2, 1)$; $(1, 1)$ to $(2, 2)$; and from $(1, 1)$ to $(1, 2)$ to pick up his $2$ flowers

In the second testcase, it can be proven that Goma can only pick up $3$ flowers at best, walking from $(1, 1)$ to $(3, 1)$.

## notes
Problem idea: chessbot

Problem preparation: chessbot

TL: 2 seconds

ML: 256mb

Occurances: Novice 3
