# Kanna's Field of Flowers

## statement

Kanna is playing a game with Saikawa! The game is played on an $N$ by $N$ $(1 \leq N \leq 2000)$ field of flowers. The flower at the $i$th row and $j$th column has color $C_{i,j}$ $(1 \leq C_{i,j} \leq 10^6)$.



A player can start at any flower and move to the right along the row until they choose to stop or they are at the edge of the field.

Let’s say they started at column $A$ and ended at column $B$. 

Then, they can repeatedly move one down along the column as long as each time they move both conditions are satisfied:

1. They are not at the edge of the field. 
2. $C_{R+1,i} = C_{R,i}$ for all $A \leq i \leq B$ where $R$ is their current row (before moving).

The score for the player is the area of the rectangle with top left corner at their starting point and bottom right corner at their ending point. For example, if Ilulu starts at row $1$ and column $1$ and ends at row $2$ and column $3$, her score is $6$. After both players finish moving, the winner is the one with the higher score.



If Kanna wins, Saikawa needs to rub her tummy as a “penalty” game. Despite being hundreds of years old, Kanna never decided to do any cp, so she asks you to figure out the maximum score she can achieve.



## Input description

The first line contains one integer, $T$ $(1 \leq T \leq 10^6)$, the number of test cases. Then $T$ test cases follow.

The first line of each test case contains an integer $N$.

The next $N$ lines describe the field of flowers. The $i$th of which contains $N$ integers, $C_{i,1}, C_{i,2}, … , C_{i,N}$.

It is guaranteed that the sum of $N^2$ over all test cases does not exceed $4 \cdot 10^6$.



## Output Description

For each test case, output the maximum score Kanna can achieve.



## sample input

```
3
1
1
2
1 2
1 2
3
1 2 5
1 2 5
4 2 5
```

## sample output

```
1
4
6
```



## sample explanation

For the first test case, Kanna can start at $(1,1)$ and end at $(1,1)$. The rectangle bounded looks like: $ \begin{pmatrix} 1 \end{pmatrix} $. The answer is $1 \cdot 1 = 1$.



------



For the second test case, Kanna can start at $(1,1)$, move to the right to $(1,2)$ and then finally move down to $(2,2)$. The rectangle bounded looks like: $ \begin{pmatrix} 1 & 2 \\ 1 & 2 \end{pmatrix} $. The answer is $ 2 \cdot 2 = 4$.



------



For the third test case, one way for Kanna to maximize her score would be to start at $(1,2)$, move to the right to $(1,3)$ and then finally move down to $(3,3)$. The rectangle bounded looks like: $ \begin{pmatrix} 2 & 5 \\ 2 & 5 \\ 2 & 5 \end{pmatrix} $. The answer is $ 3 \cdot 2 = 6$.



## notes

Problem idea: codicon/PurpleCrayon

Problem preparation: codicon

TL: 2 seconds

ML: 256mb

Occurances: Intermediate 12, Advanced 7
