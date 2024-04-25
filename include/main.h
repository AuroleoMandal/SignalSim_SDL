#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include<stdlib.h>
#include<config.h>

#define MAX_WIDTH 1980

#define SINE 0x0001
#define SQUARE 0x0002
#define SAWTOOTH 0x0004
#define REVERSESAWTOOTH 0x0008

//Stores the x and y coordinates of the points making up the wave
struct wavePoints
{
    float x,y;
};
typedef wavePoints wavePoints;


//Stores the point coordinates and all the metadata, can be modified by user_input() <userinput.h>
struct waveTemplate
{
    uint16_t flags = 0;
    
    float frequency = 1.0f;
    float amplitude = 1.0f;
    float bias = 0;
    float phase = 0;
    float duty_cycle = 0.5f;
    float high_state = 1.0f;
    float low_state = -1.0f;
    wavePoints* points = (wavePoints*)malloc(sizeof(wavePoints)*MAX_WIDTH);
};
typedef waveTemplate waveTemplate;
