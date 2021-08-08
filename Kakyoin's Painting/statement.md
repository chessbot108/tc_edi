# Kakyion's Painting

## statement

Kakyoin is painting a picture on an $N$ by $N$ grid of cells $(1 \leq N \leq 10^6)$. At first every cell in the grid contains a $0$. With each stroke of his brush, he can paint a rectangle of $1$’s where the sides of the rectangle are parallel to the sides of the grid. However, the new rectangle of $1$’s cannot cover any previously painted $1$’s and every $1$ in the rectangle cannot share a row or column with any previously painted $1$’s. At some point Kakyoin was interesting in painting, but Araki forgot and now he’s too busy using his emerald splash. So he asks you to find the sum of the number of strokes in his painting across all possible paintings that he can paint modulo $10^9 + 7$. Two paintings are considered different if the number in some cell differs between the two.



## Input description

The first line contains one integer, $T$ $(1 \leq T \leq 10^4)$, the number of test cases. Then $T$ test cases follow.

The only line of each test case contains an integer $N$.

It is guaranteed that the sum of $N$ over all test cases does not exceed $10^6$.

## Output description

For each test case, output the sum of the number of strokes in Kakyoin’s painting across all possible paintings that he can paint modulo $10^9 + 7$. 



## sample input

```
5
1
2
3
420
696969
```


## sample output

```
1
13
154
513291815
774841820
```



## sample explanation

For the first test case of the sample, there is only $1$ possible painting that uses at least one stroke: 

$ \begin{pmatrix} 1 \end{pmatrix} $

The total number of strokes is $1$.



------



For the second test case of the sample, there are $11$ possible paintings that use at least one stroke:

$ \begin{pmatrix} 1 & 0 \\ 0 & 0 \end{pmatrix} \begin{pmatrix} 0 & 1 \\ 0 & 0 \end{pmatrix} \begin{pmatrix} 0 & 0 \\ 0 & 1 \end{pmatrix} \begin{pmatrix} 0 & 0 \\ 1 & 0 \end{pmatrix} $

$ \begin{pmatrix} 1 & 1 \\ 0 & 0 \end{pmatrix} \begin{pmatrix} 0 & 1 \\ 0 & 1 \end{pmatrix} \begin{pmatrix} 0 & 0 \\ 1 & 1 \end{pmatrix} \begin{pmatrix} 1 & 0 \\ 1 & 0 \end{pmatrix} $

$ \begin{pmatrix} 1 & 0 \\ 0 & 1 \end{pmatrix} \begin{pmatrix} 0 & 1 \\ 1 & 0 \end{pmatrix} $

$ \begin{pmatrix} 1 & 1 \\ 1 & 1 \end{pmatrix} $

The total number of strokes is $ 4 \cdot 1 + 4 \cdot 1 + 2 \cdot 2 + 1 \cdot 1 = 13 $. 



## notes

Problem idea: codicon

Problem preparation: codicon

TL: 2 seconds

ML: 256mb

Occurances: Intermediate 15, Advanced 10
