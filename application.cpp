#include "application.h"

using namespace std;

Application::Application(int w, int h, bool ob, double delay) : width(w), height(h), obstacles(ob), delay(delay)
{
   nBorderWidth = 2;
   nCellSize = 15;
   sAppName = "Application";
}

int Application::screenWidth() const
{
   return width * nCellSize;
}

int Application::screenHeight() const
{
   return height * nCellSize;
}

// Called once at the start, so create things here
bool Application::OnUserCreate()
{
   colorMap[CLEAR_VALUE] = olc::GREEN;
   colorMap[TAIL_VALUE] = olc::WHITE;
   colorMap[HEAD_VALUE] = olc::BLACK;
   colorMap[FOOD_VALUE] = olc::RED;
   colorMap[OBSTACLE_VALUE] = olc::BLUE;
   colorMap[COLLISION_VALUE] = olc::DARK_YELLOW;
   nMapWidth = ScreenWidth() / nCellSize;
   nMapHeight = ScreenHeight() / nCellSize;

   playfield = new Playfield(nMapWidth, nMapHeight, obstacles);
   player = new Player();
   game = new Game(player, playfield);
   return true;
}

void Application::redraw()
{
   std::vector<std::vector<int>> grid = playfield->getGrid();
   for (int x = 0 ; x < nMapWidth ; x++)
   {
      for (int y = 0 ; y < nMapHeight ; y++)
         FillRect(x * nCellSize, y * nCellSize, nCellSize - nBorderWidth, nCellSize - nBorderWidth, colorMap[grid[y][x]]);
   }
} 

// This member function is called repeatedly until the program exits.
bool Application::OnUserUpdate(float fElapsedTime)
{
   static double gameOverTime = 0.0;
   static double stepTime = 0.0;

   redraw();

   if (stepTime + fElapsedTime * 1000.0 > delay)
   {
      if (game->isGameOver())
      {
         gameOverTime += fElapsedTime;
      }
      else
         game->makeMove();

      if (gameOverTime > 5.0)
      {
         std::cout << "Game ends.  Score = " << game->getScore() << std::endl;
         return false;
      }
      stepTime = 0.0;
   }
   stepTime += fElapsedTime * 1000.0;
 
   // If the escape or 'q' key is pressed, exit 
   return (!(GetKey(olc::Key::ESCAPE).bPressed) &&
           !(GetKey(olc::Key::Q).bPressed));
}

bool Application::OnUserDestroy()
{
   return true;
}
