# P=NP editorial

Note that this is much easier than the actual P=NP problem...



So the constraints should be small enough you can loop over all $P$ where $0 \leq P \leq X$ and all $N$ where $0 \leq N \leq Y$. 

Alternatively you can notice there is only a solution when either $P = 0$ or $N = 1$. There are $Y+1$ pairs where $P = 0$ ($\{0, 0\}, \{0, 1\}, \{0, 2\}, \cdots \{0, Y\})$ and there are also $X + 1$ pairs where $N = 0$, ($\{0, 1\}, \{1, 1\}, \{2, 1\}, \cdots \{X, 1\}$). This counts the pair ${0, 1}$ twice, so we have to subtract $1$ at the end. The end answer is $(X + 1) + (Y + 1) - 1$ or just $X + Y + 1$. Complexity $O(1)$.