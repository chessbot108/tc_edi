The problem asks us to find the size of the minimum vertex cover for the graph. However, minimum vertex cover is NP-hard, so there must be something special about this graph. Perhaps we can convert the problem from a graph problem to something else. 



In order to do this, the graph must represent something special, so let's continue to transform it and see if we can end up with anything. We know that if the sequence of cities on the path from $u$ to $v$ is increasing, then there is an edge $u - v$. Let's make graph directed so that the road between $u$ and $v$ is now a directed road from $u$ to $v$, where $u < v$. Then this property is still satisfied, because the edges point to larger values, and the property of the graph is about increasing cities on paths. Additionally, lets assign a "$time$" to each node such that $time(u) > time(v)$ where $u < v$. The property is still satisfied since the edges point back in time and paths also go back in time as they are traversed. Realize now that if instead of a “time” it was an index, the edges in the graph would be inversions of some permutation. In formal terms, the graph is both a comparability graph and a permutation graph. 



Can we retrieve the permutation from the graph? Well, the edges give us an idea about the relative positions of different numbers. An edge $u \rightarrow v$ means that $u$ must come after $v$. There are alot of missing edges though. Based on the fact that edges currently represent inversions, if there is not an edge between $u$ and $v$, where $u < v$, then $u$ comes before $v$. Thus, lets also add in an edge from $v$ to $u$, where $u < v$, if there is not an edge between the two. Let $\text{new edges}$ be the set of these edges. Now the topological sort of the graph will give us a unique permutation because edges point to numbers that come before the current number. So, when a number is pushed onto the stack that represents the permutation, all numbers that were supposed to come before it were already pushed onto the stack. Of course, there are $O(N^2)$ edges, so we need a faster algorithm. There are two options. 

The first is that we can sort the numbers $1 \, \dots \, N$ since we can find out if $u$ comes before $v$ in $O(1)$ time for the comparator. This takes $O(N \cdot log(N))$ time. 

The second is that number $u$ is at the $outdegree(u) + 1$th position since $outdegree(u)$ numbers come before it. $Outdegree(u)$ is the number of $v > u$ that come before $u$ plus the number of $v < u$ that come before $u$. Thus, $outdegree(u)$ is also the outdegree for $u$ before we added $\text{new edges}$ plus $u-1 -$ indegree for u before we added $\text{new edges}$. This takes $O(N + M)$ time. 



Now that we know the graph represents a permutation, lets see if this transformation helps to solve the problem. A vertex cover of the graph means there does not exist an edge $u - v$ such that both $u$ and $v$ are not in the set. What does this mean for the permutation? Well it means that among the numbers not in the set, there cannot be any inversions. Thus, a vertex cover is any set of nodes such that the remaining set of nodes not in the vertex cover form an increasing subsequence! Therefore, $N =$ size of vertex cover + length of remaining increasing subsequence. Which is the same as size of vertex cover $= N -$ length of remaining increasing subsequence. Thus, if we find the longest increasing subsequence, we can find the minimum vertex cover! This takes $O(N \cdot log(N))$ using a standard algorithm.



Time complexity: $O(N \cdot log(N) + M)$
