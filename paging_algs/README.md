# Paging Algorithms

This is a quick little tool to pump out the page replacement actions using some popular paging algorithms: Clock, First in First out, and Least Recently Used.

## Run

In command line:
`python3 paging.py`

## Input
```
>> Which paging alg? [c]lock, [f]ifo, or [l]ru:
c
>> Number of Pages in memory (int):
3
>> References (space separated - "A B A C B"):
a d d a f g d s f g a s d s 
```
Simply input the desired algorithm, the number of pages in memory (int), and the references to memory (space separated). 

In the above example, we are using the Clock algorithm with 3 pages and references to pages `a`, `s`, `d`, `f`, and `g` in the desired order.

## Output

The output will display the algorithm name and supplied references, then output each step of the page replacement using the selected algorithm. 

Each step displays a `Miss!` or `Hit!` that has occured. 

The Clock algorithm also displays an `(0)` or `(1)` for the clock count, `*` to denote the position of the clock, and `* CHECK` to denote it is checking for a replacement.

```
--------------------------------------------------
Clock Algorithm
--------------------------------------------------
Refs: ['a', 'd', 'd', 'a', 'f', 'g', 'd', 's', 'f', 'g', 'a', 's', 'd', 's']
--------------------------------------------------
STEP 01 [*0][a]>> * a(1) | - | - | Miss!
--------------------------------------------------
STEP 02 [*1][d]>> a(1) | * d(1) | - | Miss!
--------------------------------------------------
STEP 03 [*2][d]>> a(1) | d(1) | * - | Hit!
--------------------------------------------------
STEP 04 [*2][a]>> a(1) | d(1) | * - | Hit!
--------------------------------------------------
STEP 05 [*2][f]>> a(1) | d(1) | * f(1) | Miss!
--------------------------------------------------
STEP 06 [*0][g]>> * a(0) | d(1) | f(1) | * CHECK
--------------------------------------------------
STEP 07 [*1][g]>> a(0) | * d(0) | f(1) | * CHECK
--------------------------------------------------
STEP 08 [*2][g]>> a(0) | d(0) | * f(0) | * CHECK
--------------------------------------------------
STEP 09 [*0][g]>> * g(1) | d(0) | f(0) | REPLACE a
--------------------------------------------------
STEP 10 [*1][d]>> g(1) | * d(1) | f(0) | Hit!
--------------------------------------------------
STEP 11 [*1][s]>> g(1) | * d(0) | f(0) | * CHECK
--------------------------------------------------
STEP 12 [*2][s]>> g(1) | d(0) | * s(1) | REPLACE f
--------------------------------------------------
STEP 13 [*0][f]>> * g(0) | d(0) | s(1) | * CHECK
--------------------------------------------------
STEP 14 [*1][f]>> g(0) | * f(1) | s(1) | REPLACE d
--------------------------------------------------
STEP 15 [*2][g]>> g(1) | f(1) | * s(1) | Hit!
--------------------------------------------------
STEP 16 [*2][a]>> g(1) | f(1) | * s(0) | * CHECK
--------------------------------------------------
STEP 17 [*0][a]>> * g(0) | f(1) | s(0) | * CHECK
--------------------------------------------------
STEP 18 [*1][a]>> g(0) | * f(0) | s(0) | * CHECK
--------------------------------------------------
STEP 19 [*2][a]>> g(0) | f(0) | * a(1) | REPLACE s
--------------------------------------------------
STEP 20 [*0][s]>> * s(1) | f(0) | a(1) | REPLACE g
--------------------------------------------------
STEP 21 [*1][d]>> s(1) | * d(1) | a(1) | REPLACE f
--------------------------------------------------
STEP 22 [*2][s]>> s(1) | d(1) | * a(1) | Hit!
--------------------------------------------------
--------------------------------------------------
Hits: 5
Misses: 9
Total: 14
--------------------------------------------------
```