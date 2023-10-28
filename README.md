# Series

## About

This program calculates the probality of a baseball team winning an N-game
series, given a number of games (currently hard-coded to 7 in a constant)
and the probability that the favorite wins any individual game (also hard-
coded in a constant at this time.)

It is assumed that games are independent events (the outcome of one game
does not influence the outcome of next game in any way.)

The program currently also prints the probability of every single
potential outcome.

## Notes

This first pass at the program is crude in the sense that it keeps the entire
decision tree in RAM. I do not believe that this is necessary. Rather, I think
that a stack-based solution could be used to only keep the currently-explored
outcome in memory at any given time. 

In such an implementation, I believe the algorithm could be something like:

1. Examine the node at the top of stack.
2. If top of stack is a terminal state, accumulate stats and pop the node.
3. If top of stack is *not* terminal, push nodes for both subsequent outcomes.
4. Repeat until top of stack is the root node.

(Need to think about this more.)

## TODO

* Parameterize the program to accept user input
* Consider stack-based implementation for v2, described roughly above.
