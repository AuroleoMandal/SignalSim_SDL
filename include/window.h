#pragma once
#include<main.h>

#define CLEAR_R 150
#define CLEAR_G 150
#define CLEAR_B 170
#define CLEAR_A 255

#define AXIS_R 0
#define AXIS_G 0
#define AXIS_B 0
#define AXIS_A 200

#define SCALE_R 160
#define SCALE_G 160
#define SCALE_B 180
#define SCALE_A 100

#define QUIT 1
#define KEY_UP 2
#define KEY_DOWN 4
#define KEY_LEFT 8
#define KEY_RIGHT 16

//Initializes SDL modules
void window_INIT();

//Clears the screen
void window_clear();

//Draws markers accordinf to scale in pixels
void window_scale_markers(float, float);

//Draws axes
void window_axes();

//Polling interrupt
Uint16 window_pollEvent();

//Draws all of the waves present in waveTemplate structure array
void window_draw(waveTemplate*);

//Renders the current scene
void window_render();

