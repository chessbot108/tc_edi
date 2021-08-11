# Teleport

## statement
Chessbot would like to make it through his $N$x$M$ $(1 \leq N, M \leq 1000)$ yard in as little steps as possible going from the top left corner $(1, 1)$ to the bottom right $(N, M)$. A step consists of either going up, down, left, or right, and Chessbot cannot leave his yard. However there are a ton rocks in the way, which might hamper him, or even possibly prevent him from making it! 

Fortunately for him, there are $K (1 \leq K \leq 3 \cdot 10^5)$ one way teleporters which go from $(x_1, y_1)$ to $(x_2, y_2)$. If Chessbot steps on $(x_1, y_1)$ for a teleporter then he automatically will be teleported to $(x_2, y_2) $(i.e. he must take the teleporter). Note that this means if there is another teleporter that goes from $(x_2, y_2)$ to another point $(x_3, y_3)$, he must go through that one as well. Each starting point for a teleporter is unique.

## input format
The first line contains $N$, $M$, and $K$.

The next $N$ lines specify the layout of Chessbot’s yard, where a '#' represents a rock and a '.' represents an empty space.

The next $K$ lines each have 4 integers $x_1, y_1, x_2,$ and $y_2$ for a specific teleporter.

\*It is guaranteed that it is always possible to go from the top left to the bottom left, and that the teleporters never make a cycle (i.e. one teleporter going from $(1, 1)$ to $(2, 2)$ and another going from $(2, 2)$ to $(1, 1)$). There will never be a rock or a teleporter starting from $(1, 1)$ or $(N, M)$.

## output format
Output an integer describing the minimum amount of steps Chessbot needs to go from the top left corner of his yard to the bottom right corner.

## sample input
```
5 5 3
..#..
.#...
...#.
.##..
#....
4 1 5 2
5 2 4 4
1 2 5 2
```

## sample output
```
3
```

## sample explanation
Chessbot can move once right to go into the teleporter at $(1, 2)$, which will send him to $(5, 2)$. However there is another teleporter at $(5, 2)$ which will send him to $(4, 4)$. From there he can move once right, then once down to reach the bottom left in 3 steps.

## notes
Problem idea: Bossologist

Problem preparation: Bossologist/codicon

TL: 2 seconds

ML: 256mb

Occurances: Novice 14, Intermediate 9, Advanced 4
