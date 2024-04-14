#include<wave.h>
float x_scale = 1;
float y_scale = 1;


SDL_Point* wave_BUILD(SDL_Point* wave, struct waveVariables waveProperties)
{
    for(uint32_t pixel = 0; pixel < WIDTH; pixel ++)
    {
        wave[pixel].y = (wave_SINE(pixel, waveProperties.frequency) + WINDOW_HEIGHT/2);
        wave[pixel].x = (pixel + OFFSET);
    }
    return wave;
}

float wave_SINE(uint32_t pixel, float freq)
{
    float amplitude;
        amplitude = sin(pixel/(100.0f*x_scale)*freq)*100.0f;
    return amplitude*y_scale;
}

void wave_INCREASEX()
{
    x_scale*=1.05;
}

void wave_DECREASEX()
{
    x_scale*=0.95;
}

void wave_INCREASEY()
{
    y_scale*=1.05;
}

void wave_DECREASEY()
{
    y_scale*=0.95;
}
