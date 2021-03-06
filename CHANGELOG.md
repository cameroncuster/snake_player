April 6:
    * created the repository (csc315_spr2021_snake) and downloaded the startup
      code
    * compiled and ran the startup code
    * made first commit of startup code source with CHANGELOG

April 10:
    * Attempted BFS search, could not get implementation to work smoothly with
      interface
    * fought debugger for extensive amount of time before deciding the BFS was
      not worth it
      Tested: Graphically and with the debugger
      Data Structures: Queue (for BFS), Adjacency List to store the graph
      representation
    * brainstormed ideas extensively for more successful player

April 12:
    * Thinking about new ideas every day and different graph algorithms because
      nothing else appears to be valid
    * Use A* for searching because it will perform better than BFS, DFS, etc.
    * Idea: Dijkstra's with dynamic weighting system to prevent the snake from
      taking a path into the tail

April 14:
    * Thought about how anyone scored perfectly in the game using graph traversal
      without using an algorithm which eventually created or approximated a
      Hamiltonian Path

April 15:
    * Idea for genetic algorithm to determine weights for Dijkstra's
      dynamically throughout the search to be marketed as a "graph algorithm"
    * Idea: to use GA through evolution of random paths and evolve the top x(10)
      snakes to populate the next generation

April 17:
    * Idea to loop along self by weighting edges with A* of tail very heavily,
      and if biconnected the then become a scanner until a path becomes available
    * planning to implement one of the last two idea's, maybe both in the next
      few hours
    * going to implement GA with A* search algorithm in combination, A* tail
      coiling algorithm builds length of the snake while the GA enforces
      survival. With the focus of both algorithms the player must be successful.
    * Working to implement the GA and have been unsuccessful thus far
      Data Structures: Arrays, Sets, and Maps
      Testing: 100 Runs to validate success of the algorithm and performance,
      (Graphical) is used to analyze game play and potential issues
      Visual testing is for the purpose of generating a working implementation
      before the player is tested for performance
    * May upgrade the visual for command-line output so I can examine the moves
      executed by the snake

April 18:
    * Some success with the genetic player as a minimal improvement from the
      previous player, same data structures and algorithms (bug fixes)

      Testing: Testing is still done graphically and with 100 run script to
      evaluate the performance of the algorithm
      Data Structures: Arrays, Sets, Maps

    * Working to expand the GA for multiple generations, current success with one
      generation has been minimal as a brute a single generation GA degenerates
      to a brute force algorithm - with a prune to remove invalid moves
    * GA tracks score, but the length of the snake is not approximated correctly
      because the apples in the simulated games spawn in different locations than
      in actual gameplay so the snake thinks it is shorter/longer than it
      is in execution
    * GA is also incredibly slow and is likely to time limit given multiple
      generations
    * Potential Fixes: spawn more apples in the simulation, and count number of
      moves as opposed to score for populating (naturally selecting) the next
      generation
    * Discontinuing the GA, as it will not be the optimal approach to reasons
      listed above.
    * Going to continue to brainstorm approaches. The most fun problems take a
      lot of thought... not necessarily a lot of code.

      * GA will not successfully run for 100 runs due to generational issues

      *********************
      * Approximate Score *
      * Average: 10-15    *
      * Max Score: 20     *
      * Verified through  *
      * Graphical Runs    *
      * (Imprecise)       *
      *********************

April 20:
    * Began exploring idea for A* where heuristic follows tail of snake
    * As a more descriptive explanation, the A* heuristic is weighted so that
      nodes adjacent to the tail are preferred. Preferring nodes adjacent to the
      tail will prevent the snake from trapping itself inside it's own tail in
      many situations.
    * Pseudo implementation of the algorithm (described above) performs only
      slightly better than a traditional A* search for the food.
    * Master cleaned and branching implemented for foundational software
      development practices and proper coding standard
    * Working A* player with no heuristic, going to modify the heuristic to
      follow the tail for as long as possible (e.a. nodes adjacent to the tail
      are weighted very heavily in heuristic function)

      Testing: Visual, 100 run script, Scoreboard
      Data Structures: Priority Queue using (min-heap) for A*, Arrays (dynamic),
      Hashes, RB Trees (e.a. sets and maps (unordered and ordered)), Graph

    * Modified heuristic function for A* to follow the tail of the snake, has
      not been as effective as desired
    * Idea to modify the heurisitic function for the search to weight nodes by
      the number of reachable squares from that location in the graph (e.a. size
      of graph component), ideally the graph will always be single component
      which would eradicate the purpose of the heuristic function
    * Implemented DFS search with minimal success, the search traps itself often,
      but is blazingly fast, might be able to leverage this type of search with
      modifications to generate an approximation of a Hamiltonian Circuit
      throughout the graph
    * Idea to remove nodes from the graph as I visit them until all nodes are
      removed, the order in which the nodes are removed is an approximation of a
      Hamiltonian Circuit

April 21:
    * The modified heuristic A* has performed much better than current
      implementation of the genetic algorithm or the DFS search as shown above
    * Added GitLab runner provided by Devon Schneider with attribution
    * The GitLab runner enhances testing by ensuring all put-backs meet standard
      and should protect the runner scripts
    * Runner tests successful compilation on master when pushing to repo -
      ensures proper software development practices are being upheld (e.a. not
      inducing crashing/hanging on the runner scripts)



 ??????????????????           ?????????    ?????????    ?????????    ?????????  ??????????????????????????????????????????   ?????????????????????????????? ????????????????????????????????????????????????????????????????????? ?????????????????????
??????????????????????????? ????????????    ?????????    ?????????   ????????????    ?????????  ??????????????????????????????????????????   ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
???????????????????????? ???????????????    ????????? ?????? ?????????  ????????????     ??????????????????????????????????????????  ?????????   ??????????????????????????????????????????????????????????????????   ?????????   ???????????????
??????????????????????????????????????????    ?????????????????????????????? ????????????      ??????????????????????????????????????????  ?????????   ??????????????????????????????????????????????????????????????????   ?????????   ???????????????
?????????  ?????????  ?????????     ??????????????????????????????????????????       ?????????  ?????????????????????????????????????????????????????????????????????  ??????????????????????????????????????????   ?????????   ?????????????????????????????????

        **Performance 03x40**
        - Number Items : 100
        - Minimum Score: 8
        - Average Score: 26.99
        - Maximum Score: 51
        - Average Time : 0.00017320116

        **Performance 03x40 Obstacles**
        - Number Items : 100
        - Minimum Score: 6
        - Average Score: 20.04
        - Maximum Score: 38
        - Average Time : 0.00016551221

        **Performance 03x50**
        - Number Items : 100
        - Minimum Score: 8
        - Average Score: 32.74
        - Maximum Score: 54
        - Average Time : 0.00024140169

        **Performance 03x50 Obstacles**
        - Number Items : 100
        - Minimum Score: 10
        - Average Score: 22.26
        - Maximum Score: 41
        - Average Time : 0.00023482264

        **Performance 05x05**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 12.23
        - Maximum Score: 20
        - Average Time : 5.5967966e-05

        **Performance 05x05 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 11.51
        - Maximum Score: 20
        - Average Time : 3.2173812e-05

        **Performance 10x10**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 28.54
        - Maximum Score: 44
        - Average Time : 0.0001981253

        **Performance 10x10 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 25.19
        - Maximum Score: 48
        - Average Time : 0.00017662383

        **Performance 10x20**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 41.94
        - Maximum Score: 65
        - Average Time : 0.00044716766

        **Performance 10x20 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 33.28
        - Maximum Score: 65
        - Average Time : 0.00044996769

        **Performance 10x30**
        - Number Items : 100
        - Minimum Score: 20
        - Average Score: 53.59
        - Maximum Score: 81
        - Average Time : 0.0007309027

        **Performance 10x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 40.16
        - Maximum Score: 72
        - Average Time : 0.00075200503

        **Performance 20x20**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 63.05
        - Maximum Score: 102
        - Average Time : 0.0014349115

        **Performance 20x20 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 55.12
        - Maximum Score: 87
        - Average Time : 0.0013110053

        **Performance 20x30**
        - Number Items : 100
        - Minimum Score: 22
        - Average Score: 82.2
        - Maximum Score: 125
        - Average Time : 0.0019453767

        **Performance 20x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 5
        - Average Score: 58.65
        - Maximum Score: 106
        - Average Time : 0.002031647

        **Performance 30x30**
        - Number Items : 100
        - Minimum Score: 38
        - Average Score: 98.88
        - Maximum Score: 147
        - Average Time : 0.0051187681

        **Performance 30x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 14
        - Average Score: 79.6
        - Maximum Score: 127
        - Average Time : 0.0047613777



????????????????????? ????????????????????????????????????????????????    ?????????????????????????????????????????????????????????????????????????????????????????????
????????????????????????????????????????????????????????????????????????    ????????????????????????????????????????????????????????????????????????????????????????????????
?????????  ???????????????????????????  ????????????????????????    ????????????????????????????????????????????????????????????????????????????????????????????????
?????????  ???????????????????????????  ????????????????????????    ?????????????????????????????????????????????????????????????????????????????????????????????
?????????????????????????????????     ????????????????????????    ??????????????????????????????????????????????????????????????????????????????

        **Performance 03x40**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 13.35
        - Maximum Score: 25
        - Average Time : 1.68908787e-05

        **Performance 03x40 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 10.73
        - Maximum Score: 19
        - Average Time : 1.14984079e-05

        **Performance 03x50**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 14.9
        - Maximum Score: 34
        - Average Time : 1.82293886e-05

        **Performance 03x50 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 11.53
        - Maximum Score: 24
        - Average Time : 1.30224166e-05

        **Performance 05x05**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 13.29
        - Maximum Score: 24
        - Average Time : 1.0126861e-05

        **Performance 05x05 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 13.44
        - Maximum Score: 24
        - Average Time : 4.224104e-06

        **Performance 10x10**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 22.01
        - Maximum Score: 39
        - Average Time : 8.4804526e-06

        **Performance 10x10 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 18.61
        - Maximum Score: 41
        - Average Time : 5.3478799e-06

        **Performance 10x20**
        - Number Items : 100
        - Minimum Score: 14
        - Average Score: 26.09
        - Maximum Score: 44
        - Average Time : 6.6775643e-06

        **Performance 10x20 Obstacles**
        - Number Items : 100
        - Minimum Score: 6
        - Average Score: 20.36
        - Maximum Score: 43
        - Average Time : 4.6899362e-06

        **Performance 10x30**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 30.65
        - Maximum Score: 60
        - Average Time : 1.77620143e-05

        **Performance 10x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 22.24
        - Maximum Score: 45
        - Average Time : 9.7855535e-06

        **Performance 20x20**
        - Number Items : 100
        - Minimum Score: 10
        - Average Score: 43.71
        - Maximum Score: 72
        - Average Time : 6.5826575e-06

        **Performance 20x20 Obstacles**
        - Number Items : 100
        - Minimum Score: 4
        - Average Score: 25.33
        - Maximum Score: 52
        - Average Time : 4.2894406e-06

        **Performance 20x30**
        - Number Items : 100
        - Minimum Score: 19
        - Average Score: 46.32
        - Maximum Score: 89
        - Average Time : 7.9122999e-06

        **Performance 20x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 32.64
        - Maximum Score: 62
        - Average Time : 1.07548368e-05

        **Performance 30x30**
        - Number Items : 100
        - Minimum Score: 6
        - Average Score: 62.35
        - Maximum Score: 121
        - Average Time : 7.8880938e-06

        **Performance 30x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 9
        - Average Score: 36.82
        - Maximum Score: 72
        - Average Time : 4.2668903e-06



April 22:
    * Idea to locate a path from the food to the tail after locating and
      executing a path from the head to the food

April 23:
    * Implemented the idea from April 22, success has been the same as the A*
      with modified heuristic thus far, even with path compression which did not
      appear to improve anything (with respect to the scores)
    * Success was minimal with the continual search approach because the snake
      split the graph into multiple components a number of times
    * The snake finds paths effectively and what appears to be a cycle begins to
      develop from the snake's head around to the snake's tail, but the snake
      continues to trap itself
    * Idea to turn into larger component when pathfinding... implementation is
      the challenge here -> size of component can easily be known with a BFS,
      and a path to all elements can easily be known, but how to decide when to
      turn towards the larger component... look ahead?

      Testing: Various Size Boards (Visual), 100 Run Script, Scoreboard
      Data Structures: Sets, Maps, Hashes, Heaps, RB Trees, arrays, Graphs

April 24:
    * Updated for random searching in A* Cycle Algorithm if no path is found ->
      appears to have improved the scores (graphically)
    * scoreboard confirms my suspicion of this improvement in average/max score
    * Testing: Track minimum score
    * Idea to implement searching algorithm to search to the tail of the snake,
      then execute the moves along the path and search from that location to the
      food, then to search from the food to the head of the snake, this should
      ensure the snake can always find a path from the head to the tail
    * Just a few thoughts: I think the algorithm listed above will perform
      optimally because the path to the tail is critical, and when the snake
      loses a path to it's tail it traps itself.
    * Implementation of the above algorithm was much less effective than
      originally desired. I am going to go to bed as it is 4 A.M. and my
      algorithm was unsuccessful.

    * Testing and Data Structures remain constant

April 25:
    * Five hours of sleep later I have expanded my idea -> I need to follow the
      tail when I can not get to the food or back to the tail from the food,
      This is how I will ensure I always have a path to my tail to allow the
      cycle to develop and prevent from trapping myself
    * I think my idea (above) about requiring a path to the tail was correct,
      my implementation was incorrect: finding path to the tail before and after
      eating the food does not ensure that there path to the tail will always
      exist because in my implementation as long as 1/3 of those paths existed
      the snake would move as if all was swell not knowing it was walking right
      into it's own death
    * Tracking that all paths are found (path to food, path to tail) before
      deciding to follow the tail is critical
    * FINALLY I GOT IT TO WORK! MY IDEA WAS CORRECT!! IT DEVELOPS A CYCLE!!!
    * Implementation was much easier for this one than the previous algorithms
      besides some extra tail management
    * Added GetTail and HasObstacles member retrieval functions to the playfield
      class to reduce debug time
    * Implemented the execution of moves from the head to the food in the
      algorithm above by leveraging playfield code to create a simulation (which
      essentially a playfield with an identical interface but can me manipulated
      by my objects as friends)
    * Planning to search for optimizations to the algorithm, document code, and
      test the player

    * Testing and Data Structures remain constant

April 26:
    * Given my success yesterday the player has performed incredible. The player
      has runs which never end (infinite) because the player will never elect to
      kill itself, this also causes the code to hang at time when the snake is
      forced to eat an apple in it's path, but does not want to grow any longer
      so that the snake does not kill itself
    * Idea: I think if I searched to every empty space
      at that point to increase distance between tail and head the player would
      win every time on the playfield with no obstacles - e.a. perfect score is
      always achievable (with enough moves and logic...)
    * Must manage own tail - eradicate (Playfield::getTail())
    * Updated to not use a modified interface, and game.cpp kills infinite games
      when the number of moves without eating an apple exceeds the 10 * number of
      spots in the grid
    * Evidently the Cyclic A* Search player outperforms all of my previous
      players by orders of magnitude and could be adapted to be optimal
      Data Structures: Graph, Queue, Linked List, Array
      Testing: 100 runs script, GitLab Runner, visually tested unique board sizes
      like 3x50
    * Cyclic A* Searching Algorithm performs very well on all variations of board
      sizes + with or w/o obstacles
    * Does caching the path affect the performance? No, because the location of
      the snake tail is always accounted for (e.a. as long as a path to the tail
      exists you are good to go) - caching is faster
    * Documented and cleaned the code while writing object oriented,
      modular code
    * The new game file prevents infinite runs and allows for testing (thank you)

April 28:
    * Code is loosely coupled, and minimal
    * Code is well documented and tested
    * README with description of the algorithm is written

April 29:
    * Wrote a script to test unique/regular board sizes (3x50), etc. - Dramatic
      improvement to the testing
    * added performance to README
    * full documentation code which is written to be self-describing and
      self-documenting. The code reads like well-written prose.
    * Everything is an object with dependency injection as the design pattern

      Objects: Heuristic, Cycle, Graph, A*, Player, Simulation, Simulatefield

    * removed heuristic ^



 ??????????????????????????????   ????????? ??????????????????????????????     ????????? ?????????????????????     ???????????????
???????????????????????????????????? ?????????????????????????????????????????????     ?????????????????????????????????    ??????????????????????????? ????????????
?????????      ????????????????????? ?????????     ?????????     ??????????????????         ???????????????????????? ???????????????
?????????       ???????????????  ?????????     ?????????     ??????????????????         ??????????????????????????????????????????
????????????????????????   ?????????   ?????????????????????????????????????????????????????????????????????????????????    ?????????  ?????????  ?????????

        ## Performance ##

        **Performance 03x40**
        - Number Items : 100
        - Minimum Score: 4
        - Average Score: 32.42
        - Maximum Score: 64
        - Average Time : 5.5410929e-05

        **Performance 03x40 Obstacles**
        - Number Items : 100
        - Minimum Score: 3
        - Average Score: 12.77
        - Maximum Score: 29
        - Average Time : 7.84886016e-05

        **Performance 03x50**
        - Number Items : 100
        - Minimum Score: 4
        - Average Score: 35.58
        - Maximum Score: 80
        - Average Time : 8.582948e-05

        **Performance 03x50 Obstacles**
        - Number Items : 100
        - Minimum Score: 3
        - Average Score: 14.54
        - Maximum Score: 47
        - Average Time : 0.000111160798

        **Performance 05x05**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 19.99
        - Maximum Score: 24
        - Average Time : 7.2996362e-06

        **Performance 05x05 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 18.85
        - Maximum Score: 24
        - Average Time : 7.0007004e-06

        **Performance 10x10**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 86.28
        - Maximum Score: 100
        - Average Time : 2.0939241e-05

        **Performance 10x10 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 75.74
        - Maximum Score: 93
        - Average Time : 2.0225072e-05

        **Performance 10x20**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 159.45
        - Maximum Score: 200
        - Average Time : 5.2728318e-05

        **Performance 10x20 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 129.64
        - Maximum Score: 184
        - Average Time : 6.7121673e-05

        **Performance 10x30**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 228.13
        - Maximum Score: 297
        - Average Time : 0.00010578534

        **Performance 10x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 177.09
        - Maximum Score: 277
        - Average Time : 0.000108913163

        **Performance 20x20**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 339.94
        - Maximum Score: 400
        - Average Time : 0.000112074759

        **Performance 20x20 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 287.44
        - Maximum Score: 362
        - Average Time : 0.000108581484

        **Performance 20x30**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 496.71
        - Maximum Score: 587
        - Average Time : 0.000206559617

        **Performance 20x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 362.2
        - Maximum Score: 509
        - Average Time : 0.000269087519

        **Performance 30x30**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 763.22
        - Maximum Score: 886
        - Average Time : 0.00030139953

        **Performance 30x30 Obstacles**
        - Number Items : 100
        - Minimum Score: 1
        - Average Score: 601.45
        - Maximum Score: 775
        - Average Time : 0.0003057783



April 30:
    * added GIFS of graphical player with and without obstacles to README
    * added link to Log and development to README
    * Idea to implement the perfect player by creating tail buffer where all open
      nodes are added to the buffer between the head and tail once the player
      begins to loop infinitely this will ensure the food can always be eaten (in
      most cases) - better description of algorithm listed above
    * Fixed code hanging when apple is placed in the simulation where the apple
      is between the head and the path to the tail, preventing the snake from
      executing any valid move without killing itself
    * The fix was to not place apples in the simulation in the moveHead() routine
    * code has been tested 1000 runs at a time with the upgraded script to
      include assorted size boards to analyzing performance of a specific
      improvement at a detailed level
    * Used Valgrind to detect memory leaks, and found the start-up code does not
      delete the game in the driver, added delete game, and found there were no
      memory leaks - This was a big win for my snake (and my ability to write
      clean professional software)

      Testing: Test Script 1000+ runs, GitLab Runner, Scoreboard, Visual
      Data Structures: Same - Very Object Oriented Programming

May 1:
    * created better GIFS with more exciting runs
    * add obstacle performance to README
    * created a performance breakdown to detail the performance of the player on
      assorted boards
    * upgraded the run script for detailed output direct to the performance
      breakdown
    * read the code base
    * cleaned up old branches in the repo
    * reorganized the directory structure to resemble a professional project
    * attempted to write 'perfect player' which creates the buffer between the
      head and tail when the snake stops progressing in the game, but with little
      success.
    * Code is tested, examined for memory leaks, run 1000's of times on assorted
      game boards, and documented - Green Light
    * wrote quick script to plot players so they can be viewed graphically
