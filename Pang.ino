 /*
  PANG
 Copyright (C) 2015 Wenceslao Villanueva Jr.
 All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 */

#include <SPI.h>
#include <EEPROM.h>
//#include <Core.h>
#include "Arduboy.h"
#include <ab_printer.h>
#include "bitmaps.h"
#include "globals.h"
#include "paddle.h"
#include "ball.h"
#include "sound.h"

// GameState
// 0 = Game Not Started
// 1 = Main Menu
// 2 = In Game
// 3 = Game Over
int GameState = 0;

Paddle Paddle_1;
Paddle* Paddle_1_ptr;
Paddle Paddle_2;
Paddle* Paddle_2_ptr;
Ball GameBall;
Ball* GameBall_ptr;

int Player1Score;
int Player2Score;
int Winner;

AbPrinter TextPrinter(arduboy);

void setup() 
{
  Paddle_1_ptr = NULL;
  Paddle_2_ptr = NULL;
  GameBall_ptr = NULL;
  
  arduboy.start();
  milliPerFrame = (1.0f / targetFPS);
  lastUpdateTime = millis();
  debug = 0.0f;

  TitleXPos = screenWidth / 2 - ( 62 / 2 );

  // If Debugging, activate the Serial Monitor
  //Serial.begin( 9600 );

//  TextPrinter = new AbPrinter( arduboy );
}

void loop() 
{
  // Cap FPS at targetFPS
  if ( millis() < lastUpdateTime + milliPerFrame ) return;
  lastUpdateTime = millis();
  
  arduboy.clearDisplay();

  // Execute the loop depending on Game State
  switch ( GameState )
  {
    // Boot
    case 0:
    BootScreenLoop();
    break;
    
    // Menu
    case 1:
    MenuLoop();
    break;

    // Game
    case 2:
    GameLoop();
    break;

    // Game Over
    case 3:
      DrawGameOver();
      GameBall.Hide();
    break;
    
    default:
    break;
  }

  debug = GameBall.serveDirection;
//  arduboy.drawLine( 0, 0, 0, 128, 1);
//  arduboy.setTextSize(1);
//  arduboy.setCursor( 20,  20 );
//  arduboy.print(debug);

  arduboy.display();
}

// The Nintendo style GameBoy boot up sequence
void BootScreenLoop()
{
  arduboy.drawSlowXYBitmap( 40, ArduboyMarkerPosY, arduboyBitmap, 48, 8, 1 );
  ArduboyMarkerPosY += 10 * milliPerFrame;

  if ( ArduboyMarkerPosY >= 28 )
  {
//    ArduboyPlaytune.tone( 987, 160 );
    delay(160);
//    ArduboyPlaytune.tone( 1318, 350 );
//    ArduboyPlaytune.playScore( scoreScore );
    delay(2000);
    GameState = 1;
//    ArduboyPlaytune.playScore( titleScore );
  }
}

// The simple front end main menu
void MenuLoop()
{
  arduboy.drawSlowXYBitmap( TitleXPos, 20, title, 62, 20, 1 );
  if ( arduboy.getInput() )
  {
    GameState = 2;
    ResetGame();
    GameBall.Show();
    GameBall.Reset();
    TimeToServe = 2;
  }
}

// Perhaps not the most elegant collision system but it basically checks bounds in the X and then bounds in the Y and 
// sees if the graphics are going to collide.  This took the most time to write and I personally want
// to relearn methods of collision on hardware that doesn't run PhysX haha!
void CheckCollision()
{
  int paddle1XDelta = GameBall.posX - Paddle_1.posX;
  int paddle1YDelta = GameBall.posY - Paddle_1.posY;
  int paddle2XDelta = GameBall.posX - Paddle_2.posX;
  int paddle2YDelta = GameBall.posY - Paddle_2.posY;

  int collisionYDeltaMax_P1 = (Paddle_1.sizeY / 2) + 1 + (GameBall.ballSize / 2);
  int collisionYDeltaMax_P2 = (Paddle_2.sizeY / 2) + 1 + (GameBall.ballSize / 2);
  
  // Player 2 scored
  if ( GameBall.posX < ( -2 * GameBall.ballSize ) )
  {
    // Score
    Player2Score++;
    GameBall.Hide();
    if ( !CheckGameOver() )
    {
      GameBall.Show();
      GameBall.Reset();
      TimeToServe = TimeToServerDefault;
//      ArduboyPlaytune.playScore( scoreScore );
    }
//    else
//      ArduboyPlaytune.playScore( winScore );
  }
  // Player 1 Scored
  else if ( GameBall.posX > ( screenWidth + ( 2 * GameBall.ballSize ) ) )
  {
    // Score
    Player1Score++;
    GameBall.Hide();
    if ( !CheckGameOver() )
    {
      GameBall.Show();
      GameBall.Reset();
      TimeToServe = TimeToServerDefault;
//      ArduboyPlaytune.playScore( scoreScore );
    }
//    else
//      ArduboyPlaytune.playScore( winScore );
  }
  else if ( paddle1XDelta == ( GameBall.ballSize / 2 ) && abs(paddle1YDelta) < collisionYDeltaMax_P1 )
  {
    // Paddle 1 Hit
    float yVelocity = MapRange( paddle1YDelta * 1.0f, Paddle_1.sizeY / -2.0f, Paddle_1.sizeY / 2.0f, -ballReboundRange, ballReboundRange );
    GameBall.BounceBall( -1.05, yVelocity, 2 );
  }
  else if ( paddle2XDelta == ( GameBall.ballSize / -2 + 1) && abs(paddle2YDelta) < collisionYDeltaMax_P2 )
  {
    // Paddle 2 Hit
    float yVelocity = MapRange( paddle2YDelta, Paddle_2.sizeY / -2.0f, Paddle_2.sizeY / 2.0f, -ballReboundRange, ballReboundRange );
    debug = yVelocity;
    GameBall.BounceBall( -1.05, yVelocity, 2 );
  }
}

// The game loop!
void GameLoop()
{
  // Player One on the cross pad
  if ( arduboy.pressed( UP_BUTTON ) )
  {
    Paddle_1.Move( paddleMoveSpeed );
  }
  else if ( arduboy.pressed( DOWN_BUTTON ) )
  {
    Paddle_1.Move( -paddleMoveSpeed );
  }

  // Player Two on the A and B Buttons
  if ( arduboy.pressed( B_BUTTON ) )
  {
    Paddle_2.Move( paddleMoveSpeed );
  }
  else if ( arduboy.pressed( A_BUTTON ) )
  {
    Paddle_2.Move( -paddleMoveSpeed );
  }

  // If the ball is in play, update it
  if ( GameBall.ballInPlay )
  {
    CheckCollision();
    GameBall.Simulate();
  }
  // Otherwise we're waiting to serve
  else if ( TimeToServe > 0 )
  {
    TimeToServe -= milliPerFrame;
  }
  else if ( TimeToServe <= 0 )
  {
    GameBall.Serve();
  }

  // The half court line
  arduboy.drawLine( 63, 0, 63, 63, 1);

  // Draw all the things!!
  Paddle_1.Draw();
  Paddle_2.Draw();
  GameBall.Draw();
  DrawScores();
}

// Using built in print to put up the scores.
void DrawScores()
{
  TextPrinter.setSize( 1 );
  TextPrinter.setCursor( screenWidth / 2 - 15, 5 );
  TextPrinter.print( Player1Score );

  TextPrinter.setCursor( screenWidth / 2 + 10, 5 );
  TextPrinter.print( Player2Score );
}

// Is the game over?  If so record it and return true/false
bool CheckGameOver()
{
  if ( Player1Score >= PlayToScore )
  {
    Winner = 1;
    GameOver();
    return true;
  }
  else if ( Player2Score >= PlayToScore )
  {
    Winner = 2;
    GameOver();
    return true;
  }

  return false;
}

// Game Over!  Set the time out for the Game Over screen and update game state
void GameOver()
{
  TimeOnGameOverScreen = TimeOnGameOverScreenDefault;
  GameState = 3;  // Game Over
}

// Draw the Game Over Screen
void DrawGameOver()
{
  TextPrinter.setSize( 1 );
  TextPrinter.setCursor( screenWidth / 2 - 40, screenHeight / 2 );
  sprintf(text, "Player %u Wins!", Winner);
  TextPrinter.print( text );

  TimeOnGameOverScreen -= milliPerFrame;
  if ( TimeOnGameOverScreen <= 0 )
  {
    GameState = 1;
  }
}

// Reset the game for the next play
void ResetGame()
{
  Player1Score = 0;
  Player2Score = 0;

  int paddleStartY = (screenHeight / 2);

  if ( Paddle_1_ptr == NULL )
  {
    Paddle_1 = Paddle( PaddleXPositions - 1, paddleStartY, PaddleWidth, PaddleHeight, 1 );
    Paddle_1_ptr = &Paddle_1;
  }
  if ( Paddle_2_ptr == NULL )
  {
    Paddle_2 = Paddle( screenWidth - PaddleXPositions - 1, paddleStartY, PaddleWidth, PaddleHeight, 2 );
    Paddle_2_ptr = &Paddle_2;
  }
  if ( GameBall_ptr == NULL )
  {
    GameBall = Ball( screenWidth / 2, screenHeight / 2, 4 );
    GameBall_ptr = &GameBall;
  }
}

// Didn't see a map range function so I whipped one up really quick
float MapRange( float x, float in_min, float in_max, float out_min, float out_max )
{
  return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}



