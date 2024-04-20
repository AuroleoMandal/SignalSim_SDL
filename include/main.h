#pragma once
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640
#define OFFSET 50
#define WIDTH (WINDOW_WIDTH - OFFSET)

#define MAX_WAVES 2

#define SINE 0x0001
#define SQUARE 0x0002
#define TRIANGLE 0x0004

struct waveTemplate
{
    SDL_Point* wavepoint = new SDL_Point[WIDTH];
    uint16_t flags = 0;
    
    float frequency = 1;
    float time_period = 1.0f / frequency;
    float amplitude = 1;
    float bias = 0;
    float duty_cycle = 0.5f;
    float high_state = 1.0f;
    float low_state = -1.0f;
};
