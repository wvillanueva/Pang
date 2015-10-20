#ifndef PADDLE_H
#define PADDLE_H

#include "globals.h"

class Paddle
{
  public:
  int player;
  
  float posX;
  float posY;
  
  int sizeX;
  int sizeY;

  Paddle();
  Paddle( int x, int y, int w, int h, int p );

  void Draw();
  void Move( float direction );
};

#endif
