#include<wave.h>

static float x_scale = 1;
static float y_scale = 1;

/*  void wave_build((struct waveTemplate) waves, (unsigned 32 bit) pixel)
This function is called by wave_buildAll() multiple times, 
iterating through all of the waves (instances of waveTemplate structure array <main.h>) 
Checks waveTemplate->flags(uint16) and modifies SDL_Point* accordingly 
*/
void wave_build(waveTemplate*, uint16_t);

/*  float wave_sine((unsigned 32 bit) pixel, (floating point) frequency)
Returns the ampiltude of a Sine wave at a 
corresponding abscissa adjusted to the scale 100 pixels = 1 unit.
Scale is adjusted by user input calling the wave_increase/decrease_x/y() functions
*/
float wave_sine(uint32_t, float);

/*  float wave_square((struct waveTemplate*) waves, (unsigned 32 bit) pixel, (unsigned 16 bit) wavenumber)
Returns the ampiltude of a Square wave at a 
corresponding abscissa adjusted to the scale 100 pixels = 1 unit.
Scale is adjusted by user input calling the wave_increase/decrease_x/y() functions
*/
float wave_square(waveTemplate*, uint32_t, uint16_t);


void wave_buildAll(waveTemplate* waves)
{
    for(uint16_t wavenumber = 0; wavenumber < MAX_WAVES; wavenumber++)
    {
        wave_build(waves, wavenumber);
    }
        
}

void wave_build(waveTemplate* waves, uint16_t wavenumber)
{
    if(waves[wavenumber].flags & SINE)
    {
        for(uint32_t pixel = 0; pixel < WIDTH; pixel ++)
        {
            waves[wavenumber].wavepoint[pixel].y = \
            (-1*wave_sine(pixel, waves[wavenumber].frequency)*waves[wavenumber].amplitude)\
            + WINDOW_HEIGHT/2 + waves->bias;
            waves[wavenumber].wavepoint[pixel].x = pixel + OFFSET;
        }
    }
    if(waves[wavenumber].flags & SQUARE)
    {
        for(uint32_t pixel = 0; pixel < WIDTH; pixel ++)
        {
            waves[wavenumber].wavepoint[pixel].y = wave_square(waves, pixel, wavenumber);
            waves[wavenumber].wavepoint[pixel].x = pixel + OFFSET;
        }
    }

}


float wave_sine(uint32_t pixel, float freq)
{
    float amplitude;
        amplitude = sin(pixel/(100.0f*x_scale)*M_PI*freq)*100.0f;
    return amplitude*y_scale;
}

float wave_square(waveTemplate* waves, uint32_t pixel, uint16_t wavenumber)
{
    int highstate = (waves[wavenumber].high_state * -100 * y_scale) + WINDOW_HEIGHT/2;
    int lowstate = (waves[wavenumber].low_state * -100 * y_scale) + WINDOW_HEIGHT/2;
    float time_period = 1.0f / waves[wavenumber].frequency;
    float high_period = \
    waves[wavenumber].duty_cycle * time_period * x_scale * 100;
    int adjusted_time_period = waves[wavenumber].time_period * x_scale * 100;
    if(pixel % adjusted_time_period < high_period)
        return highstate;
    else
        return lowstate; 
}



void wave_sum(waveTemplate* waves)
{
    for(uint32_t pixel = 0; pixel < WIDTH; pixel ++)
    {
        waves[MAX_WAVES].wavepoint[pixel].y = 0;
        waves[MAX_WAVES].wavepoint[pixel].x = pixel + OFFSET;
    }
    for(uint16_t wavenumber = 0; wavenumber < MAX_WAVES; wavenumber ++)
    {
        for(uint32_t pixel = 0; pixel < WIDTH; pixel ++)
        {
            waves[MAX_WAVES].wavepoint[pixel].y = (waves[MAX_WAVES].wavepoint[pixel].y + waves[wavenumber].wavepoint[pixel].y)/2;
        }
    }

}

void wave_increaseX()
{
    x_scale*=1.05;
}

void wave_decreaseX()
{
    x_scale*=0.95;
}

void wave_increaseY()
{
    y_scale*=1.05;
}

void wave_decreaseY()
{
    y_scale*=0.95;
}
