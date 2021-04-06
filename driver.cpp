#include <iostream>
#include <chrono>
#include <vector>
#include "game.h"

using namespace std;
using namespace std::chrono;

bool checkCmdLineParams(int argc, char **argv, int &width, int &height, bool &ob)
{
   if (argc != 3 && argc != 4)
   {
      std::cout << "Usage: " << argv[0] << " width height [true/FALSE]" << std::endl;
      std::cout << "width: width of the playfield in cells" << std::endl;
      std::cout << "height: height of playfield in cells" << std::endl;
      std::cout << "[optional] add obstacles default FALSE" << std::endl;
      return false;
   }
   else
   {
      if (argc >= 3)
      {
         try
         {
            width = std::stoi(argv[1]);
            height = std::stoi(argv[2]);
            if (width < 3 || width > 68 || height < 3 || height > 60)
            {
               std::cout << "Range of valid widths is 3 - 68" << std::endl;
               std::cout << "Range of valid heights is 3 - 60" << std::endl;
               return false;
            }
         }
         catch (...)
         {
            std::cout << "Usage: " << argv[0] << " width height [true/FALSE]" <<std::endl;
            std::cout << "width: width of the playfield in cells" << std::endl;
            std::cout << "height: height of playfield in cells" << std::endl;
            std::cout << "[optional] add obstacles default FALSE" << std::endl;
            return false;
         }
      }
      if (argc == 4)
      {
         std::string obstacles(argv[3]);
         if (obstacles == "true" || obstacles == "TRUE" || obstacles == "True")
            ob = true; 
      } 
   }
   return true;
}

int main(int argc, char **argv)
{
   vector<duration<double>> turnTimes;
   time_point<system_clock> start, end;

   Player *player = new Player();
   int width, height;
   bool obstacles = false;

   if (!checkCmdLineParams(argc, argv, width, height, obstacles))
      return -1;

   Playfield *playfield = new Playfield(width, height, obstacles);
   Game *game = new Game(player, playfield);

   while (!game->isGameOver())
   {
      start = system_clock::now();
      game->makeMove();
      end = system_clock::now();
      turnTimes.push_back(end-start);
   }
   cout << "Final Score: " << game->getScore() << endl;
   
   double sum = 0.0;
   for (duration<double> d : turnTimes)
      sum += d.count();

   cout << "Average turn time: " << sum / turnTimes.size() << endl;
   return 0;
}
