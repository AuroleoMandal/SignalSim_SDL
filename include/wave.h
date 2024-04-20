#pragma once
#include<main.h>
#include<math.h>

/*  void wave_buildAll((struct waveTemplate) waves)
This function calls private function wave_build() multiple times, 
iterating through all of the waves except last (instances of waveTemplate structure array <main.h>) 
and building waves accoring to waveTemplate->flags(unsigned 16 bit int)
*/
void wave_buildAll(waveTemplate*);

/* void wave_sum((struct waveTemplate) waves)
**WIP**
Stores the sum of all but the last wave in the last waveTemplate structure
*/
void wave_sum(waveTemplate*);


//Modifies display scale, to be called by polling interrupt by user
void wave_increaseX();
void wave_decreaseX();
void wave_increaseY();
void wave_decreaseY();

