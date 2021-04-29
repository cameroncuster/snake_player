/gitlab/pipeline/:101061877/:csc315_spr2021_snake/:master

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

## Algorithm Performace ##
* Performance 100 Trials 03x50

* Performance 100 Trials 03x40

* Performance 100 Trials 05x05

* Performance 100 Trials 10x10

* Performance 100 Trials 10x20

* Performance 100 Trials 10x30

* Performance 100 Trials 20x20

* Performance 100 Trials 20x30

* Performance 100 Trials 30x30

Steps in the Pathfinding Algorithm
---
1. Locate a path to the food.
2. Simulate the path to the food.
3. Locate a path to the tail on the simulated game.
4. If either the path to the food or the path to the tail does not exist then
    follow the tail.
---

### Algorithm Development ###
[CHANGELOG](Log)

### Action Shots ###
ADD GIF OF SNAKE PLAYING for each board size
