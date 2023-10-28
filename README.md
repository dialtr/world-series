# Series

## About

Calculate the probability of a team winning an N game series given a N
and a probability that the favorite wins an individual game. This works
by building a decision tree, and assumes that the games outcomes are
independent events.

## Notes

This is a crude first pass that keeps the entire decision tree in RAM. I
do not believe this is strictly necessary. Rather, I think that a stack-
based solution could be developed that would be faster and use much less
RAM since (I think) you only ever need to keep, max, 2N items on the stack.

That can wait for version 2.
