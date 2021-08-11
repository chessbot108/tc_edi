# Making Stonks

## statement

Alex wants to make stonks so he creates his own company. He slowly hires more people over time as his company grows larger. Each person takes a certain amount of time to earn one dollar for the company, and they are not paid (Alex is a very demanding boss). He wants to buy a new campus for the company which costs $X$ dollars in order to further expand. Your job is to find how soon he is able to do so.

## input format

The first line contains two numbers, $N$ and $X$. $N$ is the amount of people he hires, $X$ is the target amount of money. $(1 \leq N \leq 10^5, 1 \leq X \leq 10^{12})$.

Next, N lines follow containing the information of each person he hires. Each line contains two numbers, $T$ and $R$, which respectively denotes the time at which the person is hired and how long it takes for them to earn one dollar. $(1 \leq T \leq 10^9, 1 \leq R \leq 10^3)$.

## output format

One number denoting the amount of time it takes for the company to reach at least $X$ dollars.


## sample input
```
3 10
1 1
3 2
3 4
```

## sample output
```
8
```

## sample explanation

The first person is hired at time 1 and makes 1 dollar at every interval, at time 8 he has made 7 dollars. The second person has made 2 dollars, and the third person has made 1 dollar. This is the earliest time that 10 dollars is reached.


## notes
Problem idea: Mantlemoose

Problem preparation: Mantlemoose

TL: 2 seconds

ML: 256mb

Occurances: Easy 10, Intermediate 3
