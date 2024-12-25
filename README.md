# Problem Statement: House Building

A number of eccentrics from New York City have decided that they have had enough of modern society, and want to move to the countryside. Together they have bought a rectangular piece of land far away from anyone else, and will settle there.

The land consists of square parcels, and it is possible to build one and only one house on any given square. Some parcels are nicer than others. Each square has a value for its desirability, L, which is an integer on a scale between 0 and 100, inclusive.

The happiness an eccentric experiences from building their house on any given parcel is the parcel's desirability, L, times its distance to the nearest house, D:
    (L*D)

Out of habit, the eccentrics use "Manhattan distance" to measure D. Manhattan distance refers to the distance a person would have to drive to get between 2 points when the streets form a grid. Total distance is measured by the sum of vertical travel plus horizontal travel, with no diagonal travel.
Thus, the distance between 2 houses located at (x1, y1) and (x2, y2) is defined as:
    D = abs(x1-x2) + abs(y1-y2)

The eccentrics now want your help in maximizing their collective happiness, so that the sum of all their happiness scores is as high as possible. However, they are impatient, so your program needs to produce its best answer within 10 seconds.

Multiple groups of eccentrics want help. Each run of your program will provide a solution for a single group, for their particular plot of land.


## Input:
Each run of your program will be given input to "standard in"/stdin consisting of:
- A line of 3 space-separated integer numbers W, H, and N:
  - W: Width of the grid, should be >0 and <=1000
  - H: Height of the grid, should be >0 and <=1000
  - N: Number of houses, should be >1 and <=MIN(W*H, 10000)
- H lines containing W space-separated integers, each describing the value of the plot of land in the corresponding x, y position. Each value will be >= 0 and <= 100.

The x, y positions are defined as 1, 1 being the top left, and W, H being the bottom right.


## Output:
Your output should go to "standard output"/stdout, as N lines of the positions of the houses. Each line will describe the (x, y) position of one house as the column (between 1 and W inclusive) and row (between 1 and H inclusive). 2 houses may not be placed at the same position.

If an input is invalid you may produce any output, as long as you exit with a non-zero return code promptly and not crash.


Real programs must deal with invalid inputs, thus handling invalid inputs is part of the evaluation.


## The following will all be considered failure of the evaluation:
- Running for more than 10 seconds after you have been supplied with the inputs
- Crashing
- Producing invalid or extraneous output/not following the output specification

For the output, do not output anything other than a newline separated list of house positions. In particular, don't:
- Output the happiness
- Output a prompt
- Output 3 backticks in a row (that is part of the markdown formatting this file is written in)


## Example 1:

### Input:
```
4 3 2
100 1  10 0
0   10 13 100
7   15 18 40
```

### Valid Output:
```
1 1
4 2
```

### Collective Happiness Score:
For this example input and output, the collective happiness score would be 800 because:
- The two houses are a Manhattan distance of 4 apart
- The first house is at position 1, 1, with a value of 100, so their happiness is 400.
- The second house is at a position 4, 2, with a value of 100, so their happiness is 400
- Added together they are 800.

For the sake of example, another valid output would be:
```
1 1
4 3
```
Then the score would be 700 because:
- The 2 houses are now a distance of 5 apart
- First house has a happiness of 500 (100 value * 5 distance) now
- Second house has a happiness of 200 (40 value * 5 distance)
- Added together makes 700

Your goal is to maximize the collective happiness, so the first output is superior to the second.


## Example 2:

### Input:
```
5 5 3
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
```

### Valid Output:
```
1 1
1 2
1 3
```

### Collective Happiness Score:
For this example input and output, the collective happiness score would be 3 because each house is distance 1 from its nearest neighbor, and the land value of each house is 1.

Note that this is not the optimal result, though it is correct. A question for you to answer is what is a better result, and what is the optimal result?


# Evaluation Scoring:
Your program will be scored on a range of test cases that you will not have access to. You will need to come up with an approach that can handle a wide variety of cases (including invalid inputs), and produce the best collective happiness.

This programming challenge is intended to evaluate your ability to write code to
solve difficult programming problems where it may not be practical to produce a
perfect solution in the time available, but merely a "good" one.

Here are the evaluation criteria for this challenge:

1. The most important is that the solution must produce a correct result, even
   if it is not optimal. Your program may only execute for 10 seconds of wall
   clock time, executing for any longer will be considered an incorrect result.

2. The solution should be as good as you are able to make it for as many cases
   as you can think of.

3. Quality of the code and associated work products, such as use of git to track
   changes, test cases generated, error checking, comments, design, etc.
