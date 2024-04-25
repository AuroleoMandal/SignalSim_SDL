#pragma once
#include<main.h>

#define QUIT 1
#define REDRAW 2
#define MOUSEWHEEL_UP 4
#define MOUSEWHEEL_DOWN 8
#define KEY_UP 16
#define KEY_DOWN 32
#define KEY_LEFT 64
#define KEY_RIGHT 128


//Initializes SDL modules
int window_INIT(uint32_t window_width, uint32_t window_height);

void window_getsize(uint32_t *window_width, uint32_t *window_height);

//Clears the screen
void window_clear();

//Draws axes
void window_axes(uint32_t window_width, uint32_t window_height);

//Draws markers according to scale in pixels
void window_scale_markers(uint32_t window_width, uint32_t window_height, float x_scale, float y_scale);

//Polling interrupt
Uint16 window_pollEvent();

//Draws all of the waves present in waveTemplate structure array
void window_draw(waveTemplate*, uint32_t window_width, uint32_t window_height);

//Renders the current scene
void window_render();

