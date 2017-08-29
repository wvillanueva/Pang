#include "ball.h"

Ball::Ball() {}

Ball::Ball( int x, int y, int s )
{
  xV = 0;
  yV = 0;
  serveVelocity = 12;
  posX = x;
  posY = y;
  ballSize = s;
  serveDirection = 1;  // Serve Left, then alternate
  ballInPlay = false;
  rendering = false;
}

void Ball::Simulate()
{
  if ( ballInPlay == false ) return;
  
  posX = posX + xV * milliPerFrame;
  posY = posY + yV * milliPerFrame * 2;

  // Hit the top of the screen
  if ( ( posY - ( ballSize / 2 ) ) < 0 )
  {
    BounceBall( 1.0f, -yV * 2.0f, 1 );
    posY = posY + yV * milliPerFrame;
  }
  // Hit the bottom of the screen
  if ( posY + ( ballSize / 2 ) > screenHeight )
  {
    BounceBall( 1.0f, -yV * 2.0f, 1 );
    posY = posY + yV * milliPerFrame * 2;
  }
}

void Ball::Draw()
{
  if ( rendering ) arduboy.drawRect( posX - ballSize / 2, posY - ballSize / 2, ballSize, ballSize, 1);
}

void Ball::Serve()
{
  ballInPlay = true;
  xV = serveVelocity * serveDirection;
}

void Ball::BounceBall(float dX, float dY, int soundType) // Change direction by sign of argument
{
  xV = xV * dX;
  yV = dY;
  yV = constrain( yV, -ballReboundRange, ballReboundRange );

  // Wall
  if ( soundType == 1 )
    tunes.tone(294, 100);
  // Paddle
  else if ( soundType = 2 )
    tunes.tone(622, 100);
}

void Ball::Reset()
{
  ballInPlay = false;
  xV = 0;
  yV = 0;
  posX = screenWidth / 2 - 1;
  posY = screenHeight /2 - 1;
  serveDirection *= -1;
}

void Ball::Show()
{
  rendering = true;
}

void Ball::Hide()
{
  rendering = false;
  ballInPlay = false;
}

