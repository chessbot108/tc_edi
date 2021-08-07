# Tree Width Editorial

Note: I probably overestimated the difficulty of this problem. I made a solution that ran in $O(n \cdot tree\ depth)$ that might have used linear memory if i changed it. Most submissions ran in $O(n \cdot tree\ depth)$ memory as well as time. I didn't realize it was so much easier to implement using a bottom up method if you could store the entire dp table without mle.



The first important observation is that the height of a modtree is rather small, you could have arrived at this conclusion from guessing, seeing that it's close to a random tree and random tree's have low depths, or making the assumption that the height of the modtree is log2 since mod is half. By running a $5e5^2$ brute force you can find that the largest depth a modtree goes up to is $42$ with $n =493919$ .



## definitions

Let's define $cnt[i][j]$ as the amount of nodes with distance $j$ away from node $i$. Node $i$ has distance $0$ from itself.

Now let's define $temp[i][j]$ as the amount of nodes in node $i$'s subtree. (Note we root the tree at node $0$). 

$par[i]$ is the parent of node $i$, parent of the root is undefined.

$dep[i]$ is the depth of node $i$, $dep[0]$ = $0$.

## solution

Then we have
$$
cnt[i][j] = cnt[par[i]][j - 1] + temp[u][j] - temp[u][j - 2]
$$
Note that in this equation if ever you access a negative index, it is just $0$.

 

So in words, the amount of nodes distance $j$ away from node $i$ is

1. the amount of nodes distance $j - 1$ from the parent of $i$. This is the amount of nodes up the tree that contribute to the answer. Note this overcounts since there are also some nodes with distance $j - 1$ from $par[i]$ within $i's$ subtree. We will handle the overcount in case 3
2. the amount of nodes distance $j$ from node $i$ in $i's$ subtree. This is the contribution down the tree on in $i's$ subtree.
3. subtract the amount of of nodes in $i's$ subtree distance $j - 2$ from node $i$. These are the nodes that are overcounted in case 1. Since these nodes have distance $j - 1$ from $par[i]$ but do not have distance $j$ from node $i$. 

The answer is then $\max(cnt[i][j])$ over all $i$ and all $j$. 

I think most teams made the above observations, but our implementations are different.

So let's say I find $cnt[0][j]$ for all $j$. Then I want to transition from each parent to their child. We can just compute the $temp$ array for the child and then loop over all relevant $j$ and recompute $cnt[i][j]$ and take the max. The I repeat the process from the children. The total complexity runs in $O(\sum_{i = 0}^{n-1} subtree \ size\  of\ i)$. This evaluates to $O(n \cdot tree\ depth)$. Consider the sum of all subtrees of all nodes with a fixed depth from the root. The sum of all of these subtrees is at most $n$ since each node can only belong to one subtree of a node of a certain depth. So the sum of all subtrees is around $O(n \cdot tree\ depth)$. 



In my implementation, I don't actually store all $cnt$ and $temp$ values. Instead whenever I recurse, I first store the values in the $cnt$ array, but then I edit the array and restore it at the end.



```cpp
#include <iostream>
#include <cassert>
#include <vector>
#define pb push_back

const int MX = 5e5 +10;
using namespace std;

int dep[MX]; //max distance leaf
int cnt[MX], temp[MX]; //cnt and temp...
int cpy[MX][50]; //my way of storing the answer
vector<int> adj[MX];
int n;

int ans = 0; //answer in a global counter

int dfs1(int u, int p){ //compute dep
	dep[u] = 0;
	for(int v : adj[u]){
		if(v != p){
			dep[u] = max(dep[u], dfs1(v, u) +1);
		}
	}
	return dep[u]; //if u is a leaf, the dep[u] will still be 0
}	

void dfs2(int u, int p, int d){ //computing temp
	temp[d]++;
	for(int v : adj[u]){
		if(v != p){
			dfs2(v, u, d+1);
		}
	}
}

void dfs3(int u, int p, int d){ //actual answer finding
	for(int i = 0; i<=dep[u]; i++){
		cpy[i][d] = cnt[i]; //1. copying down the answer
	}
	for(int i = 0; i<=dep[u]; i++){
		temp[i] = 0; //temp isnt all 0's from the previous use of it
	}
	dfs2(u, p, 0); //2. compute temp
	if(u == 1){ 
		for(int i = 0; i<=dep[u]; i++){ 
			cnt[i] = temp[i]; //case when u is the root
		}
	}else{
		for(int i = dep[u]; i >= 0; i--){
			cnt[i] = (i > 0 ? cnt[i-1] : 0) + (temp[i] - ((i > 1) ? temp[i-2] : 0)); 
			//3. recompute cnt
		}
	}
	for(int i = 0; i<=dep[u]; i++){
		ans = max(ans, cnt[i]); //4. account for the answer
	}
	for(int v : adj[u]){
		if(v != p){
			dfs3(v, u, d+1); //5. dfs again
		}
	}
	for(int i = 0; i<=dep[u]; i++){
		cnt[i] = cpy[i][d]; //6. restoring answer
	}
}

int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int T; cin >> T;
	while(T--){
		cin >> n;
		ans = 0;
		for(int i = 0; i<=n+1; i++){
			cnt[i] = temp[i] = dep[i] = 0;
			adj[i].clear();
			for(int j = 0; j<50; j++) cpy[i][j] = 0;
		}
		for(int i = 1; i<n; i++){
			int a = i, b = n%i;
			a++, b++; //making the tree 1-based
			adj[a].pb(b);
			adj[b].pb(a);
		}
		dfs1(1, 0);
		dfs3(1, 0, 0);
		cout << ans << "\n";
	}
	return 0;
}


```

