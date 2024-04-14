#pragma once
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640
#define OFFSET 50
#define WIDTH (WINDOW_WIDTH - OFFSET)

struct waveVariables
{
    float frequency = 1;
    float bias = 0;
};