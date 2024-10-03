# parm_algo
A basic implementation of parm algorithm.

# How to run
```bash
g++ -o ans asn.cpp
./ans
./ans
Frequent itemset found between band 0 and band 1
P-tree root count: 4
0 0 1 0 0 0
0 0 0 1 0 0
1 1 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

Frequent itemset found between band 0 and band 2
P-tree root count: 7
1 0 1 1 0 0
0 1 0 1 0 0
1 0 0 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

Frequent itemset found between band 0 and band 3
P-tree root count: 5
0 0 0 1 0 0
0 1 0 1 0 0
0 0 0 1 0 0
0 0 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

Frequent itemset found between band 1 and band 2
P-tree root count: 5
0 0 1 0 0 0
0 0 1 1 0 0
1 0 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

Frequent itemset found between band 1 and band 3
P-tree root count: 4
0 1 0 0 0 0
1 0 0 1 0 0
0 0 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

Frequent itemset found between band 2 and band 3
P-tree root count: 5
0 0 0 1 0 0
0 1 0 1 0 0
0 0 1 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

Association Rules:
Rule: {0 } -> {1 } with confidence: 44.4444%
Rule: {1 } -> {0 } with confidence: 44.4444%
Rule: {0 } -> {2 } with confidence: 77.7778%
Rule: {2 } -> {0 } with confidence: 70%
Rule: {0 } -> {3 } with confidence: 55.5556%
Rule: {3 } -> {0 } with confidence: 55.5556%
Rule: {1 } -> {2 } with confidence: 55.5556%
Rule: {2 } -> {1 } with confidence: 50%
Rule: {1 } -> {3 } with confidence: 44.4444%
Rule: {3 } -> {1 } with confidence: 44.4444%
Rule: {2 } -> {3 } with confidence: 50%
Rule: {3 } -> {2 } with confidence: 55.5556%
