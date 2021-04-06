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

   if (argc != 3 && argc != 4)
   {
      std::cout << "Usage: " << argv[0] << " width height [true/FALSE]" << std::endl;
      std::cout << "width: width of the playfield in cells" << std::endl;
      std::cout << "height: height of playfield in cells" << std::endl;
      std::cout << "[optional] add obstacles default FALSE" << std::endl;
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
            return -1;
         }
      }
      if (argc == 4)
      {
         std::string obstacles(argv[3]);
         if (obstacles == "true" || obstacles == "TRUE" || obstacles == "True")
            ob = true; 
      } 
      Application demo(width, height, ob);
      if (demo.Construct(demo.screenWidth(), demo.screenHeight(), 1, 1))
         demo.Start();
   }
   return 0;
}
