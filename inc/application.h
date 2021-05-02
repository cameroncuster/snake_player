#ifndef APPLICATION_H
#define APPLICATION_H
#include <vector>
#include <map>
#include "olcPixelGameEngine.h"
#include "game.h"

class Application : public olc::PixelGameEngine
{
   int width, height;
   bool obstacles;
   double delay;
   int nMapWidth;
   int nMapHeight;
   int nCellSize;
   int nBorderWidth;
   Playfield *playfield;
   Player *player;
   Game *game;
   std::map<int, olc::Pixel> colorMap;
public:
   Application(int, int, bool obstacles, double d);

public:
   bool OnUserCreate() override;
   bool OnUserUpdate(float) override;
   bool OnUserDestroy() override;
   void redraw();
   int screenWidth() const;
   int screenHeight() const;
};

#endif
