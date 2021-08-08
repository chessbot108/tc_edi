# Abc's (Easy Version)

## statement

Elijah is playing against a computer in a game called ‘ABCs’, where each side takes turns playing the letter $A$, $B$, or $C$, with the computer going first. Every time Elijah plays a letter, he gets a point if and only if it is a card that the computer has played the most of up until that point (ties included). For example if the computer has played $AABC$, Elijah will only get a point if he plays $A$, but if the computer has played $ACBBC$ then Elijah will get a point whether he plays a $B$ or a $C$. 

Being the trickster that he is, Elijah hacked into the game and found out the exact order the computer will play the letters. Unfortunately for him, the game found out about this trickery, and decided to punish him by only allowing him to play a single letter every turn (i.e. either all $A$s, all $B$s or all $C$s). Elijah wants to make the best of the situation, and wants to compute to maximum possible of points he can achieve.

## Input format

The first line contains $N (1 \leq N \leq 10^5)$, denoting the number of turns. The next line contains a string with $N$ characters describing what letters the computer will play in the game (as obtained by Elijah’s nefarious hacking).

## Output format

Output the maximum points that Elijah can achieve if he is only allowed to play one letter the entire game.

## sample input
```
9 
ABBCCCBAB
```

## sample output
```
7
```

## sample explanation

If Elijah plays all $B$’s, he will get a point for each turn except for the 1st and 6th one.

## notes
Problem idea: Bossologist
Problem preparation: Bossologist
TL: 2 seconds
ML: 256mb
Occurances: Novice 4

