# Necklaces

## statement
Because he was so grateful of the flowers he received, Peach wants to make a necklace for Goma (how sweet!) . He starts off with a straight line of $N$ beads labeled $1$ to $N$ $(1 \leq N \leq 4 \cdot 10^5)$ all held together with a string. Peach quickly realizes however, that the necklace would be way too long, so he decides to cut it at certain places to shorten the necklace. As he is cutting the necklace, he wants to know how many beads share a single string with a certain bead.

## input format
The first line contains $N$ and $M$ $(1 \leq M \leq 4 \cdot 10^5)$.

The next $M$ lines contain a character and an integer, $c$ and $i$ respectively. If $c$ is 'R’, that means Peach cuts the string in between beads $i$ and $i + 1$. Otherwise if $c$ is ‘Q’, then Peach would like to know how many beads share the same string as bead $i$, including bead $i$. $(1 \leq i \leq N - 1)$

## output format
Every time $c$ is ‘Q’, output the answer to the query.

## sample input
```
6 6
R 2
R 4
Q 1
R 1
Q 6
Q 2
```

## sample output
```
2
2
1
```

## sample explanation
The necklace starts off like this

0-0-0-0-0-0 

After the first and second cut it then looks like this

0-0 0-0 0-0 

There are two beads on the same string as bead 1

After the third cut out necklace looks like

0 0 0-0 0-0

Two beads share the same string as bead 6, and bead 2 is the only bead on the string.

## notes
Problem idea: Bossologist

Problem preparation: Bossologist

TL: 2 seconds

ML: 256mb

Occurances: Novice 9, Intermediate 6, Advanced 1
