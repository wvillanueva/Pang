#include "globals.h"

Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);

int screenWidth = 128;
int screenHeight = 64;
int targetFPS = 60;
float milliPerFrame = 0;
unsigned long lastUpdateTime = 0;
char text[16];      //General string buffer

//
// Game Settings
//
int PlayToScore = 3;

float TimeToServe;
float TimeToServerDefault = 2;
float TimeOnGameOverScreen = 5;
float TimeOnGameOverScreenDefault = 5;

int PaddleWidth = 5;
int PaddleHeight = 15;
int PaddleXPositions = 10;
float paddleMoveSpeed = 0.3f;

float ballReboundRange = 4.0f;

// Presentation stuffs
float ArduboyMarkerPosY = -8;
int TitleXPos;

// Debugging
float debug;
