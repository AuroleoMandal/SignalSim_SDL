#pragma once
#include<main.h>
#include<math.h>

/*  void wave_build(struct waveTemplate, x_scale, y_scale) 
Iterates through all of the waves except last (instances of waveTemplate structure array <main.h>) 
and building waves accoring to waveTemplate->flags(unsigned 16 bit int)
Last element is reserved for storing the sum of all the previous waves
*/
void wave_build(waveTemplate*, uint32_t window_width, uint32_t window_height, float x_scale, float y_scale);



