#include "paddle.h"

Paddle::Paddle() {}

Paddle::Paddle( int x, int y, int w, int h, int p )
{
  player = p;
  posX = x;
  posY = y;
  sizeX = w;
  sizeY = h;
}

void Paddle::Draw()
{
  if ( player == 1 )
  {
    arduboy.fillRect( posX - (sizeX - 1), posY - (sizeY / 2), sizeX, sizeY, 1 );
  }
  else
  {
    arduboy.fillRect( posX, posY - (sizeY / 2), sizeX, sizeY, 1 );
  }
}

void Paddle::Move( float direction )
{
  posY = posY - direction;
  if ( posY < ( sizeY / 2 ) )
  {
    posY = (sizeY / 2);
  }
  else if ( posY > ( screenHeight - ( sizeY / 2 )  ) ) 
  {
    posY = screenHeight - ( sizeY / 2 );
  }
}

