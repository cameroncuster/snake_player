#define OLC_PGE_APPLICATION
#include <iostream>
#include <string>
#include "application.h"

void usage()
{
   std::cout << "snake width height [" << std::endl;
}

int main(int argc, char *argv[])
{
   int width, height;
   bool ob = false;
   double delay = 0.0;

   if (argc != 3 && argc != 4 && argc != 5)
   {
      std::cout << "Usage: " << argv[0] << " width height [true/FALSE]" << std::endl;
      std::cout << "width: width of the playfield in cells" << std::endl;
      std::cout << "height: height of playfield in cells" << std::endl;
      std::cout << "[optional] add obstacles default FALSE" << std::endl;
      std::cout << "[optional] delay between timesteps [ms]" << std::endl;
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
               return -1;
            }
         }
         catch (...)
         {
            std::cout << "Usage: " << argv[0] << " width height [true/FALSE]" <<std::endl;
            std::cout << "width: width of the playfield in cells" << std::endl;
            std::cout << "height: height of playfield in cells" << std::endl;
            std::cout << "[optional] add obstacles default FALSE" << std::endl;
            std::cout << "[optional] delay between timesteps [ms]" << std::endl;
            return -1;
         }
      }
      if (argc >= 4)
      {
         std::string obstacles(argv[3]);
         if (obstacles == "true" || obstacles == "TRUE" || obstacles == "True")
            ob = true; 
      }
      if (argc == 5)
      {
         try
         {
            delay = std::stoi(argv[4]);
            if (delay < 0.0)
            {
               std::cout << "Delay cannot be negative" << std::endl;
               return -1;
            }
         }
         catch (...)
         {
            std::cout << "Usage: " << argv[0] << " width height [true/FALSE]" <<std::endl;
            std::cout << "width: width of the playfield in cells" << std::endl;
            std::cout << "height: height of playfield in cells" << std::endl;
            std::cout << "[optional] add obstacles default FALSE" << std::endl;
            std::cout << "[optional] delay between timesteps [ms]" << std::endl;
            return -1;
         }
      }
      Application demo(width, height, ob, delay);
      if (demo.Construct(demo.screenWidth(), demo.screenHeight(), 1, 1))
         demo.Start();
   }
   return 0;
}
