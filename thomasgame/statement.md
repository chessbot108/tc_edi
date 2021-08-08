# Thomas Game

## Statement

Thomas has been caught game! The game he is playing is defly, a game of flying a plane to connect dots, (Note this is slightly different from the actual game). In the game, you have a set of $N$ points $(5 \leq N \leq 5 \cdot 10^5)$ and you want to draw a convex polygon around the points such that all the points are contained within it. To use less effort, Thomas is using his skills to minimize the area of such a polygon (more formally these things are called convex hulls). Teacher got mad and destroyed two points in Thomas's set of points, but Thomas does not know which points these are. So he would like to ask you $Q$ queries $(1 \leq Q \leq 5 \cdot 10^5)$ where each query is defined as two indices $a$ and $b$ $(1 \leq a, b \leq N, a \neq b)$, and Thomas would like to know what the are of the convex hull of the entire array without those two points would be. 

Also, note since the problem setter, chessbot, does not like making edge cases, all of the points will be randomly generated using the following code: 

https://pastebin.com/LjfHKxtN

## input format

The first line will contain two integers $N$, $Q$ $(5 \leq N \leq 5 \cdot 10^5, 1 \leq Q \leq 5 \cdot 10^5)$. The following $N$ lines will contain two integers each, the $x$ and $y$ coordinates of each of the $N$ points $(1 \leq x,y \leq 10^9)$. The following $Q$ lines will contain two integers each, $a$ and $b$ representing the query $(1 \leq a, b \leq N, a \neq b)$. 

Note that despite the points being randomly generated, the queries will not be randomly generated but rather made to fit the previously generated points.

## output format

$Q$ lines, one integer per line representing the answers to the queries. The $i$th line should be the area of the convex hull with the points $a$ and $b$ of the $i$th query removed multiplied by two. Note that with the given constraints the answer will always fit within a $64$-bit integer.

Again, make sure you find the area of the convex hull multiplied by two.

## sample input
```
5 2
1 1
1 5
5 5
5 1
3 3
1 2
3 5
```

## sample output

```
8
16
```

## sample explanation
The input points look something like a $4$x$4$ grid with corners at $(1, 1)$, $(1, 5)$, $(5, 5)$, and $(5, 1)$ with one point at the center, $(3, 3)$. 

In the first query, we are removing points $(1, 1)$ and $(1, 5)$. The remaining points, $(1, 5)$, $(3, 3)$, and $(5, 5)$ make up a triangle that is $45$-$45$-$90$ and has side lengths $2 \cdot \sqrt{2}, 2 \cdot \sqrt{2}, 4$. The area is $(2 \cdot \sqrt{2}   \cdot  2 \cdot \sqrt{2})/2$, which is $4$ (proof is left as an exercise to the reader). Then multiply the area by $2$ and the answer is $8$.

In the second query we are removing points $(5, 5)$ and $(3, 3)$, leaving us with $(1, 1)$, $(1, 5)$, and $(5, 1)$. This also gives us a $45$-$45$-$90$ triangle but with side lengths $4$, $4$, $4 \cdot \sqrt{2}$. The area of the figure (or the convex hull of the figure, they are the same in this case) is $((4 \cdot 4)/2)$ or $8$. Multiply that by $2$ to get $16$.

## notes
Problem idea: chessbot/PurpleCrayon
Problem preparation: chessbot
TL: 2 seconds
ML: 256mb
Occurances: Advanced 13
