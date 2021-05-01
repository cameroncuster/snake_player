# Snake Player - Cameron Custer #
Well-written implementation in C++ of generic snake player for the classic "Snake
Game." Player is dictated only by SSSP graph traversal algorithms. The player was
developed through a series of trail and error. Initally I intended to develop a
Genetic Algorithm for the game of Snake, but this was unsuccessful as you can
read from my log. I also attempted using DFS and BFS (SSSP) algorithms for
pathfinding, but AStar yeilded the best performance and allowed me to integrate
my own heuristic function. While the integration of the heuristic was
unsuccessful, the pathfinding algorithm has performed better than expected.
Behaviors evolved from the player which had not been accounted for in the code.
For example, upon watching the snake graphically I noticed if the food is
surrounded by the snakes tail the snake will position more space between the
food of the snake and the snakes tail to allow the snake to eat the food.
Overall the algorithm gave outstanding performance, frequency acheiving a perfect
score, and nearing a perfect score almost every run. The player also handles non-
traditional size grids well (with or without obstacles).

## Performace ##
**Performance 03x40**
- Number Items : 100
- Average Score: 30.18
- Maximum Score: 86
- Average Time : 6.6939978e-05

**Performance 03x40 Obstacles**
- Number Items : 100
- Average Score: 13.6
- Maximum Score: 45
- Average Time : 7.65015901e-05

**Performance 03x50**
- Number Items : 100
- Average Score: 35.57
- Maximum Score: 77
- Average Time : 9.6168116e-05

**Performance 03x50 Obstacles**
- Number Items : 100
- Average Score: 13.22
- Maximum Score: 38
- Average Time : 0.000118964425

**Performance 05x05**
- Number Items : 100
- Average Score: 18.89
- Maximum Score: 24
- Average Time : 8.5778528e-06

**Performance 05x05 Obstacles**
- Number Items : 100
- Average Score: 18.55
- Maximum Score: 24
- Average Time : 8.0428159e-06

**Performance 10x10**
- Number Items : 100
- Average Score: 84.4
- Maximum Score: 100
- Average Time : 2.39310373e-05

**Performance 10x10 Obstacles**
- Number Items : 100
- Average Score: 73.3
- Maximum Score: 93
- Average Time : 2.5738813e-05

**Performance 10x20**
- Number Items : 100
- Average Score: 157.39
- Maximum Score: 200
- Average Time : 5.8234758e-05

**Performance 10x20 Obstacles**
- Number Items : 100
- Average Score: 132.83
- Maximum Score: 179
- Average Time : 5.2111296e-05

**Performance 10x30**
- Number Items : 100
- Average Score: 241.76
- Maximum Score: 300
- Average Time : 7.8603747e-05

**Performance 10x30 Obstacles**
- Number Items : 100
- Average Score: 194.38
- Maximum Score: 271
- Average Time : 0.000103391617

**Performance 20x20**
- Number Items : 100
- Average Score: 351.78
- Maximum Score: 396
- Average Time : 8.6326409e-05

**Performance 20x20 Obstacles**
- Number Items : 100
- Average Score: 297.29
- Maximum Score: 357
- Average Time : 8.6697314e-05

**Performance 20x30**
- Number Items : 100
- Average Score: 498.61
- Maximum Score: 598
- Average Time : 0.00012643826

**Performance 20x30 Obstacles**
- Number Items : 100
- Average Score: 378.8
- Maximum Score: 512
- Average Time : 0.000187150924

**Performance 30x30**
- Number Items : 100
- Average Score: 755.65
- Maximum Score: 883
- Average Time : 0.00019038416

**Performance 30x30 Obstacles**
- Number Items : 100
- Average Score: 618.47
- Maximum Score: 759
- Average Time : 0.00027685104

Steps in the Pathfinding Algorithm
---
1. Locate a path to the food.
2. Simulate the path to the food.
3. Locate a path to the tail on the simulated game.
4. If either the path to the food or the path to the tail does not exist then
    follow the tail.
---

### Development Process ###
[CHANGELOG](Log)

### Action Shots ###
![Gif of snake player execution on 20x20 board](snake20x20.gif)
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
![Gif of snake player with obstacles execution on 20x20 board](snakeObstacles20x20.gif)

&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;

![Gif of snake player execution on 3x50 board](snake20x20.gif)
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
![Gif of snake player with obstacles execution on 20x20 board](snakeObstacles20x20.gif)
