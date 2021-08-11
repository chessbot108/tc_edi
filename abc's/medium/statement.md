# Abc's (Hard Version)

## statement 

For a second time, Elijah is playing against a computer in a game called ‘ABCs’, where each side takes turns playing the letter $A$, $B$, or $C$, with the computer going first. Every time Elijah plays a letter, he gets a point if and only if it is a card that the computer has played the most of up until that point (ties included). For example if the computer has played $AABC$, Elijah will only get a point if he plays $A$, but if the computer has played $ACBBC$ then Elijah will get a point whether he plays a $B$ or a $C$. 

Being the trickster that he is, Elijah hacked into the game and found out the exact order the computer will play the letters. Unfortunately for him, the game found out about this trickery, and this time decided to punish him by only allowing him switch letters after playing the same letter at least $K$ consecutive times. Elijah wants to make the best of the situation, and wants to compute to maximum possible of points he can achieve.

## input format

The first line contains $N (1 \leq N \leq 10^5)$, denoting the number of turns, and $K (1 \leq K \leq N)$. The next line contains a string with $N$ characters describing what letters the computer will play in the game (as obtained by Elijah’s nefarious hacking).

## output format

Output the maximum points that Elijah can achieve if he is only allowed to switch letters after playing the same letter at least $K$ consecutive times.

## sample input
```
9 3
ABBCCCBAB
```

## sample output
```
8
```

## sample explanation

If Elijah plays $BBBBCCCBB$, he gets a point on every turn except the first one.

## notes

Problem idea: Bossologist/PurpleCrayon

Problem preparation: Bossologist

TL: 2 seconds

ML: 256 mb

Occurances: Novice 15, Intermediate 10, Advanced 5
