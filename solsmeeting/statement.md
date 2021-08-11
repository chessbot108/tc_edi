# Sol's Problem Meeting

## statement

Sol is trying to get home at location $N$ from his office at location $1$ in time for the problem writing meeting which is in $K$ minutes. There are $M$ bidirectional roads which connect location $a$ to location $b$, each taking $w$ minutes to go through, and each raising his angriness to $f$ when passing through the road (Sol is very irritated by traffic). But because he is generally quite calm, at each location his angriness resets back to 0. To stop himself from road raging he wants to minimize his maximum angriness at any point in time.

However, this is not Sol's only challenge. The logistics team is trying to sabotage Sol's trip by making him as angry as possible (the problem writing team is their arch enemy). They do this by closing down a single road that will cause him to endure the most angriness on his drive to his home. Please output the minimal maximum angriness that Sol has to endure on his trip home given that he has to make it in $K$ minutes, and the logistics team has shut down one of the roads.

## input format

The first line contains $N$, $M$, and $K$, where $N$ is the number of intersections $(1 \leq N \leq 10000, 1 \leq M \leq 50000, 1 \leq K \leq 10^9)$.

The next $M$ lines have 4 integers which specify that road. The first two integers are the locations it connects, $a$ and $b$ $(a \neq b)$. The next integer is $w$ or how long it take in minutes to go through that road, and $f$ or how angry sol gets when crossing that road $(1 \leq a, b \leq N, 1 \leq w \leq 10^4, 1 \leq f \leq 10^9)$. Each pair of locations will have at most $1$ road.

## output format

A single integer denoting the minimal maximum angriness that Sol has to endure on his trip home given that he has to make it in $K$ minutes, and the logistics team has shut down one of the roads. If it is not possible for him to make it in K minutes or less, output $-1$.

## sample input
```
4 6 9
1 2 4 2 
1 3 8 1
1 4 8 4
2 3 3 2
2 4 7 2
3 4 2 3
```

## sample output
```
4
```

## sample explanation

If the logistics team wasn't in the way, then Sol could go $1 \rightarrow 2 \rightarrow 3 \rightarrow 4$ which would get him to his house in $9$ minutes, and give a maximum angriness of $3$. However, they could have sabotaged one of these roads. So worst case he gets to his house using $1 \rightarrow 4$ with angriness $4$ and in $8$ minutes which is enough time.

## notes
Problem idea: Bossologist/PurpleCrayon

Problem preparation: Bossologist/codicon

TL: 2 seconds

ML: 256mb

Occurances: Advanced 14
