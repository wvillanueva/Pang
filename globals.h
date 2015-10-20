#ifndef GLOBALS_H
#define GLOABLS_H

#include "Arduboy.h"

extern Arduboy arduboy;
extern int screenWidth;
extern int screenHeight;
extern int targetFPS;
extern float milliPerFrame;
extern unsigned long lastUpdateTime;
extern char text[16];      //General string buffer

// Game Settings
extern int PlayToScore;

extern float TimeToServe;
extern float TimeToServerDefault;
extern float TimeOnGameOverScreen;
extern float TimeOnGameOverScreenDefault;

extern int PaddleWidth;
extern int PaddleHeight;
extern int PaddleXPositions;
extern float paddleMoveSpeed;

extern float ballReboundRange;

// When you boot the system, this is where the ARDUBOY intro starts from
extern float ArduboyMarkerPosY;
// Contains the calculated value for where the X Position is for the "PANG" Title 
extern int TitleXPos;

// A variable to hold debug data that I can output on screen
extern float debug;

#endif
