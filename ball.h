#ifndef BALL_H
#define BALL_H

#include "globals.h"

class Ball
{
  public:

    Ball();
    Ball( int x, int y, int s );

    float xV;
    float yV;
    int serveVelocity;
    float posX;
    float posY;
    int ballSize;
    int serveDirection;
    bool ballInPlay;
    bool rendering;

    void Simulate();
    void Draw();
    void Serve();
    void BounceBall( float dX, float dY, int soundType );  // Direction by sign
    void Reset();
    void Show();
    void Hide();
};

#endif
