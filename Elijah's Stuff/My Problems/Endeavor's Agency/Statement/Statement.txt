Formal:
An undirected graph is beautiful if for every edge u-v, you can create a new graph with either directed edge u->v or u<-v such that for every path from a to b, there exists a directed edge from a to b. You are given an undirected graph with N (N <= 10^5) nodes and M (M <= 10^5) edges. Somehow both the graph and its complement are both beautiful! Find the minimum vertex cover of the graph.


Final:
Endeavor is a great hero and wants to help keep his country, Japan, safe. Japan contains $N (1 \leq N \leq 10^5)$ cities numbered from $1$ to $N$. There are also $M (0 \leq M \leq 5 \cdot 10^5)$ bidirectional roads where the $i$th connects city $M_{i,a}$ to city $M_{i,b} \, (M_{i,a} \neq M_{i,b})$ and makes the two cities neighbors. It is guaranteed that there is at most $1$ road between any pair of cities. Japan also has a peculiar feature. Consider a path that visits $w$ cities from city $u$ to city $v$, where the $i$th city on the path is $p_i$. Then if $p_i < p_{i+1}$ for all $i<w$, city $u$ and city $v$ are neighbors. 

Endeavor decides to build a hero office in some cities. To ensure safety and efficiency, he wants at least one of the conditions to be satisfied for every city:
	1. The city has no neighbors.
	2. The city contains an office.
	3. All neighbors of the city contain an office.
Japan is considered safe if this requirement is met. 

Unfortunately, as great of a hero as Endeavor is, he still hasn’t defeated the greatest villain—money! To cut down on costs, Endeavor’s agency decides to build the minimal number of offices such that Japan is safe. Currently, Endeavor is busy roasting evildoers (literally), so he wants you to find this out for him.

https://cdn.discordapp.com/attachments/742604968573272158/869682836863614987/unknown.png


Extra Final (might use in place of some sentence later):
Consider a path from city $u$ to city $v$ where the path is the cities on the path. Then if the path is increasing, city $u$ and city $v$ are neighbors.


Input:
The first line contains one integer, $T (1 \leq T \leq 10^5)$, the number of test cases. Then $T$ test cases follow.

The first line of each test case contains $2$ integers, $N, M$.

The next $M$ lines of each test case contain $2$ integers. The $i$th such line contains $M_{i,a}, M_{i,b}$.

It is guaranteed that the sum of $N$ over all test cases does not exceed $10^5$. It is also guaranteed that the sum of $M$ over all test cases does not exceed $5 \cdot 10^5$. 


Output:
For each test case, output the minimal number of offices to build such that Japan is safe.



Sample Explanation:

Here’s the country from first test case:
https://cdn.discordapp.com/attachments/742604968573272158/870525395064217641/test_case_1.png

In the first test case, there is only a single city, so no offices need to be added. The answer is $0$.


Here’s the country from second test case:
https://cdn.discordapp.com/attachments/742604968573272158/870525400265162782/test_case_2.png

In the second test case, there are $3$ cities and $1$ road. A road connects city $2$ to city $3$. To minimize the offices built, Endeavor can build an office in either city $2$ or city $3$. The answer is $1$.


Here’s the country from third test case:
https://cdn.discordapp.com/attachments/742604968573272158/870525402144202752/test_case_3.png

In the third test case, there are $4$ cities and $3$ roads. There is a road that connects city $3$ to city $1$, a road that connects city $4$ to city $2$, and a road that connects city $2$ to city $3$. To minimize the offices built, one solution is for Endeavor to build an office in city $1$ and city $2$. Of course, building offices in cities $(1,2), \, (3,2),$ or $(3,4)$ all work to achieve the minimal number of offices. The answer is $2$.


Images:
https://cdn.discordapp.com/attachments/742604968573272158/869682836863614987/unknown.png

Image for sample explanation:

https://cdn.discordapp.com/attachments/742604968573272158/870525395064217641/test_case_1.png

https://cdn.discordapp.com/attachments/742604968573272158/870525400265162782/test_case_2.png

https://cdn.discordapp.com/attachments/742604968573272158/870525402144202752/test_case_3.png
