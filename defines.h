#ifndef DEFINES_H
#define DEFINES_H
#include <utility>

// Some helpful macros, enums, and constants

enum ValidMove {NONE, LEFT, RIGHT, UP, DOWN};

const std::string MoveNames[] = {"None", "Left", "Right", "Up", "Down"};

const std::vector<std::pair<int, int>> translate =
{
   {std::make_pair( 0,  0)}, /* NONE  */
   {std::make_pair( 0, -1)}, /* LEFT  */
   {std::make_pair( 0,  1)}, /* RIGHT */
   {std::make_pair(-1,  0)}, /* UP    */
   {std::make_pair( 1,  0)}  /* DOWN  */
};

const std::pair<int, int> invalid_food_location {-1, -1};

#define CLEAR_VALUE 0
#define TAIL_VALUE 1
#define HEAD_VALUE 2
#define FOOD_VALUE 4
#define OBSTACLE_VALUE 8
#define COLLISION_VALUE 16
#define OutOfBounds(x) ((x.first < 0 || x.first >= height || \
                         x.second < 0 || x.second >= width))

#define validRow(r) (r >= 0 && r < height)
#define validCol(c) (c >= 0 && c < width)
#define canEnter(r, c) (validRow(r) && validCol(c) && \
                       (grid[r][c] != TAIL_VALUE && \
                        grid[r][c] != OBSTACLE_VALUE && \
                        grid[r][c] != COLLISION_VALUE))
 
#endif
