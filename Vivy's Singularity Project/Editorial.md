
Consider a graph where there is an edge $i \rightarrow j$ if $j$ is a child of $i$. The singularity project is successful if the final graph of events is a line. There are an exponential number of ways we can create this line, so we are motivated to use dynamic programming. 



When an event occurs, it must be the child of one of the endpoints for the graph to remain a line. This means we only need to keep track of the endpoints in our dp. Let $DP[i][j]$ be the probability that we create a line graph with events $i$ and $j$ as endpoints after $i$ events have occured. Let $P(j)$ be the probability that the $i$th event is a child of event $j$. Then, $P(j) = (\lfloor \frac{X}{i} \rfloor +  (j < X \mod i))/X$. Our base case is $DP[1][0] = 1$. The transitions are as follows: 

$$DP[i][i-1] = \sum_{j = 0}^{i-2} P(j) \cdot DP[i-1][j]$$. 

$$DP[i][j] = P(i-1) \cdot DP[i-1][j], \, 0 \leq j < i-1$$.

Thus, we already have an $O(N^2)$ solution to the problem. 



How can we do better? Notice that for the first type transition to compute $DP[i][i-1]$, $P(j)$ only takes on at most $2$ values. From $j = 0 \, \dots \, (X \mod i) - 1$, $P(j)$ is $\lfloor \frac{X}{i} \rfloor + 1$ and from $(X \mod i) \, \dots \, i-2$, $P(j)$ is $\lfloor \frac{X}{i} \rfloor$. Thus, the $j$ that have the same value of $P(j)$ are contiguous. We simply need to find $\sum DP[i-1][j]$ for the $2$ ranges. Notice that for the second type of transition, we are simply multiplying each value in the range $DPi-1][0 \, \dots \, i-2]$ by $P(i-1)$. 

Does this sound familiar? Well, we can use a segment tree with lazy propagation to handle these range sum and range multiply queries. In the $i$th iteration, the array that the segment tree represents will be $DP[i]$. Updating the segment tree to represent $DP[i+1]$ from $DP[i]$ requires only $4$ queries each of which take $log(n)$ time, so the time complexity is $O(N \cdot log(N))$.



Time complexity: $O(N \cdot log(N))$.
