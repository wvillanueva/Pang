# Pang
A Pong-like for Arudoby!

Description
PANG is a Pong-Like for Arudoby! It's a digital game of tennis that harkens back to the games that first launched the idea of a game console. Play two players on one Arduboy or see how long you can volley by yourself!

I got my dev kit the other night and I've never done Arduino development so after cutting my teeth on the Dev Env and API I whipped up a Pong-like. It was mostly built in two evenings. I'm quite happy with myself. Please post comments, feedback, etc.

Instructions
First player to score 3 points wins! Move your paddle up and down to meet the ball and hit it back to your opponent. If you get it passed your opponent, you score a point! The ball speeds up as the volley goes on so be quick!

Installation
1) Download Zip or Git Clone from: https://github.com/wvillanueva/Pang9
2) Open Pang.ino with Arduino IDE
3) Upload to your Arduboy

Version 1.0
First version. My first Arduboy and Arduino project. Mostly completed in a couple of nights. I feel that there are some inefficiencies in the code that someone will let me know about. I may try to reduce the footprint in future versions. 66% for a Pong-Like? Sheesh!

Known Bugs:

If you volley long enough the ball will speed up to the point that it goes through the paddle. The solution is to base collision on forward interpolation but even then, eventually it will just jump across the screen.
