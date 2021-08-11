# Matching Mispronunciations

## statement
Cameron the cashier works as a cashier in a beverage store. The store manager wants the menu of the beverages to change weekly, however the sizes of the cups would stay the same as Small, Medium, Large. Over the week, every customer got 1 letter of each word of their order wrong (meaning that the word was the same, including it's length and all other letters of the word except for one letter), and mispronounced their order.

For example, one week the manager decided to sell Lemonade and Punch. A customer asked for a Smell Panch. The actual order the customer was asking for would be the Small Punch. Assuming all the names of the beverages are one word (in the order of size of cup then beverage name “Small Punch”), and assuming that a mispronunciation can’t be a mispronunciation of more than one word, help Cameron understand what the customers were asking for.

## input format

The first line has an integer $1 < N < 1000$, representing the number of orders.

The next $N$ 3-line chunks represent the details of the order. The first line of the 3-line chunk has one integer, $1 < A < 100$ where $A$ represents the amount of different beverages. The second line of the 3-line chunk contains $A$ space-separated words representing the names of the beverages. The length of the words will be $3 \leq X \leq 13$. The third line of the 3-line chunk contains two words, which is the order. The first word represents the cup size and the second word represents the beverage name.

## output format
Print the actual order’s name of each order, each on different lines.

## sample input
```
2
4
water lemonade punch juice
melium wader
2
coffee tea
mediuf tee
```

## sample output
```
medium water
medium tea
```

## sample explanation

## notes
Problem idea: Spark
Problem preparation: Spark
TL: 2 seconds
ML: 256mb
Occurances: Novice 7, Intermediate 2
