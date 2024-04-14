#pragma once
#include<main.h>
#include<math.h>

//Build waves according to parameters and flags
SDL_Point* wave_BUILD(SDL_Point*, struct waveVariables);

void wave_INCREASEX();
void wave_DECREASEX();
void wave_INCREASEY();
void wave_DECREASEY();

float wave_SINE(uint32_t, float);