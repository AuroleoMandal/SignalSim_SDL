#include<wave.h>

/*  float wave_sine(waveTemplate structure, abscissa)
Returns the ampiltude of a Sine wave at a 
corresponding abscissa adjusted to the scale passed to wave_build().
*/
float wave_sine(waveTemplate, float);

/*  float wave_square(waveTemplate structure, abscissa)
Returns the ampiltude of a Square wave at a 
corresponding abscissa adjusted to the scale passed to wave_build().
*/
float wave_square(waveTemplate, float);


void wave_build(waveTemplate* waves, uint32_t window_width, uint32_t window_height, float x_scale, float y_scale)
{
    for(uint16_t wavenumber = 0; wavenumber < MAX_WAVES; wavenumber++)
    {
        for(uint32_t pixel = 0; pixel < window_width; pixel ++)
        {
            float abscissa = pixel/x_scale;
            waves[wavenumber].points[pixel].x = pixel;

            if(waves[wavenumber].flags & SINE)
                waves[wavenumber].points[pixel].y = wave_sine(waves[wavenumber], abscissa) * y_scale;
        
            if(waves[wavenumber].flags & SQUARE)
                waves[wavenumber].points[pixel].y = wave_square(waves[wavenumber], abscissa) * y_scale;
        }
    }

    //Assign the value of 0 to all y coordinates of the wave holding the summation
    //(Last element in the waveTemplate structure array)
    for(uint32_t pixel = 0; pixel < window_width; pixel ++)
    {
        waves[MAX_WAVES].points[pixel].y = 0;
        waves[MAX_WAVES].points[pixel].x = pixel;
    }
    
    //Iteratively add all the waves to wave holding the summation
    for(uint16_t wavenumber = 0; wavenumber < MAX_WAVES; wavenumber ++)
    {
        for(uint32_t pixel = 0; pixel < window_width; pixel ++)
        {
            if(wavenumber == 0)
                waves[MAX_WAVES].points[pixel].y = waves[wavenumber].points[pixel].y;
            else
                waves[MAX_WAVES].points[pixel].y = \
                (waves[MAX_WAVES].points[pixel].y + waves[wavenumber].points[pixel].y)/2;
        }
    }
}


float wave_sine(waveTemplate waves, float abscissa)
{
    float amplitude;
    amplitude = sin(abscissa * waves.frequency) * waves.amplitude;
    return amplitude;
}

float wave_square(waveTemplate waves, float abscissa)
{
    float time_period = 1.0f/waves.frequency;
    float high_period = \
    waves.duty_cycle * time_period;
    return (fmodf(abscissa, time_period) < high_period)?\
    -waves.high_state : -waves.low_state;
}