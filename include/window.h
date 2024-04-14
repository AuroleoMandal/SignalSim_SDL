#pragma once
#include<main.h>

#define CLEAR_R 190
#define CLEAR_G 190
#define CLEAR_B 190
#define CLEAR_A 255

#define AXIS_R 0
#define AXIS_G 0
#define AXIS_B 0
#define AXIS_A 255

#define QUIT 1
#define KEY_UP 2
#define KEY_DOWN 4
#define KEY_LEFT 8
#define KEY_RIGHT 16


void window_INIT();
void window_CLEAR();
void window_AXES();
Uint16 window_POLLEVENT();
void window_DRAW(SDL_Point*);
void window_RENDER();