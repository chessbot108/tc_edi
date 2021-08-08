# Vivy's Singularity Project

## statement

Vivy is carrying out the singularity project! She is currently at the start of everything at event $0$. Unfortunately, $N$ $(1 \leq N \leq 10^5) $ more timeline changing events are about to occur. Luckily, Vivy has picked a special number $X$ $(1 \leq X \leq 10^9)$ to assist her project. When the $i$th event occurs, a random number $A$ from $0$ to $X-1$ is generated. Then, it becomes possible to go from event $(A \mod i)$ to event $i$ and event $i$ is considered a child of event $(A \mod i)$. If after all events occur, event $0$ has more than $2$ children or there exists an event $i$ such that $i > 0$ and it has more than $1$ child, the timeline becomes unstable and only a tragic future where AIs are bent on eradicating humanity awaits. If no such event exists, the singularity project is successful and humans and AIs live happily ever after. As Vivy’s partner, you want to test the value of $X$ and determine the probability that the singularity project is successful.

## input format

The first line contains one integer, $T$ $(1 \leq T \leq 10^5)$, the number of test cases. Then $T$ test cases follow.

The first and only line of each test case contains two integers, $N, X$.

It is guaranteed that the sum of $N$ over all test cases does not exceed $10^5$.

## output format

The probability that the singularity project is successful for each test case can be expressed as a fraction $\frac{P}{Q}$. For each test case, output $P \cdot Q^{-1}$ modulo $10^9+7$. $Q^{-1}$ is the modular inverse of $Q$, so $Q \cdot Q^{-1} \equiv 1 \mod 10^9+7$.

## sample input

```
5
1 1
2 3
3 5
4 7
42069 123456789
```

## sample output
```
1
1
200000002
250728865
734982873
```

## sample explanation

For the first test case, event $1$ must be a child of event $0$ because the random number $A$ must be $0$ and $0 \mod 1 = 0$. We end up with timeline $0 \rightarrow 1$. Event $1$ has no children and event $0$ has $1$ child, so the singularity project was successful. The probability and answer is $1$.


For the second test case, again, event $1$ must be a child of event $0$. Additionally, event $2$ must be a child of event $0$ or event $1$. We end up with either timeline $2 \leftarrow 0 \rightarrow 1$ or $0 \rightarrow 1 \rightarrow 2$. In either case, event $0$ has at most $2$ children and no event $i$ such that $i > 0$ has more than $1$ child. The probability and answer is $1$.


For the third test case, again, event $1$ must be a child of event $0$. Event $2$ is a child of event $0$ when the random number $A$ is $0,2,$ or $4$ and a child of event $1$ when $A$ is $1$ or $3$. Thus the timeline $2 \leftarrow 0 \rightarrow 1$ occurs with probability $ \frac{3}{5} $ and the timeline $0 \rightarrow 1 \rightarrow 2$ occurs with probability $\frac{2}{5}$. For the first timeline, event $3$ is a child of event $2$ when the random number $A$ is $2$, a child of event $1$ when $A$ is $1$ or $4$, and a child of event $0$ when $A$ is $0$ or $3$. If event $3$ is a child of event $0$, event $0$ has more than $2$ children and the timeline becomes unstable. It is fine for event $3$ to be a child of event $1$ or $2$ though. Thus, the timeline $3 \leftarrow 2 \leftarrow 0 \rightarrow 1$ occurs with probability $\frac{3}{25}$ and the timeline $2 \leftarrow 0 \rightarrow 1 \rightarrow 3$ occurs with probability $\frac{6}{25}$. Similarly, the timeline $0 \rightarrow 1 \rightarrow 2 \rightarrow 3$ occurs with probability $\frac{2}{25}$ and the timeline $3 \leftarrow 0 \rightarrow 1 \rightarrow 2$ occurs with probability $\frac{4}{25}$. These are all the final timelines where the singularity project is successful. The probability is thus $\frac{3 + 6 + 2 + 4}{25} = \frac{3}{5} $. Since $3 \cdot 5^{-1} \equiv 3 \cdot 400000003 \equiv 200000002 \mod 10^9 + 7$, the answer is $200000002$.

## notes
Problem idea: codicon/PurpleCrayon
Problem preparation: codicon
TL: 2 seconds
ML: 256mb
Occurances: Intermediate 14, Advanced 9
