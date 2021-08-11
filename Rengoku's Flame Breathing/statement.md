# Rengoku's Flame Breathing

## statement

Rengoku is battling a powerful demon! This demon has $N$ $(1 \leq N \leq 10^5)$ hearts where the $i$th heart has health $H_i$ $(1 \leq H_i \leq N)$. Luckily for Rengoku, he practices Flame Breathing and knows $K$ $(2 \leq K \leq 2 \cdot 10^5)$ different forms. In one attack, he picks a random heart $i$ such that $H_i > 0$ and also picks a random form $F$ from $1$ to $K$. Then he uses the $F$th form on the $i$th heart, reducing its health to $\lfloor \frac{H_i}{F} \rfloor$ (floor division). The demon is slain after the health of all its hearts drops to $0$. As Rengoku’s kouhai, he assigns you the task of finding the expected number of attacks he will use to slay the demon.



## Input description



The first line contains one integer, $T$ $(1 \leq T \leq 10^5)$, the number of test cases. Then $T$ test cases follow.

The first line of each test case contains two integers, $N, K$.

The second line of each test case contains $N$ integers, $H_1, H_2, … , H_N$.

It is guaranteed that the sum of $N$ over all test cases does not exceed $10^5$.



## Output description

The expected number of attacks Rengoku will use to slay the demon for each test case can be expressed as a fraction $\frac{P}{Q}$. For each test case, output $P \cdot Q^{-1}$ modulo $10^9+7$. $Q^{-1}$ is the modular inverse of $Q$, so $Q \cdot Q^{-1} \equiv 1 \mod 10^9+7$.



## sample input

```
3
1 2
1
2 2
1 2
3 3
1 2 3
```

## sample output

```
2
6
750000012
```



## Sample explanation

For the first test case, the demon has a single heart with health $1$. There is a $ \frac{1}{2} $ chance that Rengoku uses his $2$nd form and reduces the demon's health to $ \lfloor \frac{1}{2} \rfloor = 0 $. There is also a $ \frac{1}{2} $ chance that Rengoku uses his $1$st form and the demon's health is not affected because it changes to $\lfloor \frac{1}{1} \rfloor = 1$. It may take Rengoku many attacks because he might repeatedly pick the $1$st form. It turns out that the answer is $2$.



## notes

Problem idea: codicon

Problem preparation: codicon 

TL: 2 seconds

ML: 256mb

Occurances: Advanced 11
