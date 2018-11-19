# Illumio-Coding-Challenge
This repository contains my coding assignment for Illumio

Testing My Code

In order to test my code, I made use of the basic test cases that were given in the assignment specifications.
In addition, I also wrote two other test cases, one to check the edge case for range inputs for IP addresses and ports and another for checking an IP address input in a given range.
Fortunately, the second custon test case revealed a bug in my code, although that meant I spent my remaining timr fixing that issue and I couldn't add any further test case.

Design Choices

I used a struct to contain all the information for a Rule and decided to use a vector of rules to include all the rules in the input.
I decided to use unsigned ints, and bools for some of the parameters of a rule which could make the program more memory effecient for larger data sets.
I also changed the input to a istringstream to allow easier testing, but can be easily changes to a filestream to match the specification.

Refinements that could have been made with more time.

I realize that C++ isn't the ideal language for easy string manipulation considering I have to find the index of each '.', ',', '-', everytime. This project would have been much simpler if I used python or Java instead. Unfortunately, by the time I realized that, it was too late.
I do realize some of the string comparisons can be expensive in large datasets and there couls have been a more effecient way to tackle it, although I have minimized it in several situations using bools and ints instead.

Teams listed in order of my interest.

1.Policy Team
2.Platform Team
3.Data Team
