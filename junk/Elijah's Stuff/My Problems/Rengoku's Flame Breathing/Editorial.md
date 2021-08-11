The first thing to notice is that the expected number of attacks to reduce the health of a heart to $0$ is independent of other hearts. Thus, we can find the expected number of attacks for each heart and then add these together to get the final answer. 

UwU

There are an endless number of ways Rengoku can reduce the health of a heart to $0$ and after using a form, the health of the heart changes to a new smaller value (unless it is the first form). This motivates us to use dynamic programming. Let $DP[i]$ be the expected number of attacks to reduce a heart of health $i$ to $0$. Of course, $DP[0] = 0$. It follows that:

$$DP[i] = \sum_{F = 1}^{K} (DP\left[\left\lfloor \frac{i}{F} \right\rfloor\right] + 1)/K$$​​​​​

UwU

An issue arises though. What happens if $F = 1$​​​​​? Let $E$​​​​​ be the expected number of attacks used after Rengoku finally chooses a form $F != 1$​​​​​. 

Then the expected number of attacks is $E + (E+(K-1)/K)/K + (E+2 \cdot (K-1)/K)/K^2 \dots$​​​​ ​​(He does not pick $F=1$​​​​, he picks $F=1$​​​​ one time with probability $1/K$​​​, he picks $F=1$​​​ two times with probability $1/K^2$​​​​ and so forth). This is an arithmetico-geometric series and the sum ends up being: $$(K \cdot E + 1)/(K-1)$$

You can use either a "double" geometric series or the formula for the sum of an infinite arithmetico-geometric series to find this final sum. 

Alternatively (and more nicely), $DP[i] = E + (1 + DP[i])/K$​, so we can find $DP[i]$​ with simple algebra. 

There are $O(N)$ states and $O(N)$ transitions, so we already have an $O(N^2)$​ solution. 

UwU

How can we do better? Well intuitively, $\left\lfloor \frac{N}{F} \right\rfloor$​​ seems like it takes on the same value quite a few times for large values of $F$​​. In fact, it only takes on $O(\sqrt N)$​​ values! Let's try to prove this. 

For the values $ \geq \sqrt N$​​, we choose $F = 1, \, 2, \, \dots \, , \, \lfloor \sqrt N \rfloor$​​ (if $N < \lfloor \sqrt N \rfloor \cdot (\lfloor \sqrt N \rfloor +1), \, \left\lfloor \frac{N}{\sqrt N} \right\rfloor < \sqrt N$​​, so handle this edge case). These are all the possible values $ \geq \sqrt N$​​ since if we try $F = \sqrt N + 1$​​, $\left\lfloor \frac{N}{F} \right\rfloor < \sqrt N$​​​. 

Now for values $ < \sqrt N$​​​​, realize we can cleverly choose $F = \left\lfloor \frac{N}{j} \right\rfloor$​​​​ for $j = 1, \, 2, \, \dots \, , \, \lfloor \sqrt N \rfloor$​​​​ to attain values $1, \, 2, \, \dots \, , \, \lfloor \sqrt N \rfloor$​​​​ (if $N$​​​​ is a perfect square, discard the last value, $\lfloor \sqrt N \rfloor$​​​​ to avoid double count with the $ \geq \sqrt N$​​​​ case). These are all the possible values $< \sqrt N$​​​​ since we attain every possible one. This is true because $\left\lfloor N/ {\left\lfloor \frac{N}{j} \right\rfloor} \right\rfloor = j$​​​​ for $j < \sqrt N$​​​​. To show this, let $\left\lfloor \frac{N}{j} \right\rfloor = a$​​​​. Then $N$​​​​ is some value from $a \cdot j$​​​​ to $a \cdot j + j-1$​​​​. Thus, $\left\lfloor \frac{N}{a} \right\rfloor = j$​​​​ since $a \geq j$​​​​. 

It turns out that $\left\lfloor \frac{N}{j} \right\rfloor$​​​​​​ is the largest $F$​​​​​ such that $\left\lfloor \frac{N}{F} \right\rfloor = j$​​​​​. This is true because by definition of $\left\lfloor \frac{N}{j} \right\rfloor = F$​​​​​, $F$​​​​​ is the largest number such that $F \cdot j \leq N$​​​​​. This means the range from $F = \left\lfloor \frac{N}{j+1} \right\rfloor + 1 \, \dots \, \left\lfloor \frac{N}{j} \right\rfloor$​​​​​ will result in $\left\lfloor \frac{N}{F} \right\rfloor = j$​​​​​​. 

Using these facts, we can optimize our dp to $O(N \cdot \sqrt N)$​!

UwU

Time complexity: $O(N \cdot \sqrt N)$​





