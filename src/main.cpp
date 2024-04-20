#include<main.h>
#include<userinput.h>
#include<window.h>
#include<wave.h>

uint16_t running = 1;

waveTemplate waves[MAX_WAVES+1];

int main(int argc, char* args[])
{
    user_input(waves);


    window_INIT();
    while (running)
    { 
        wave_buildAll(waves);
        wave_sum(waves);
        window_clear();
        window_axes();
        
        window_scale_markers();

        switch(window_pollEvent())
        {
            case QUIT:
                running = 0;
            case KEY_UP:
                wave_increaseY();
                break;
            case KEY_DOWN:
                wave_decreaseY();
                break;
            case KEY_LEFT:
                wave_decreaseX();
                break;
            case KEY_RIGHT:
                wave_increaseX();
                break;
        }
        for(uint16_t wavenumber = 0; wavenumber < MAX_WAVES; wavenumber++)
        {
            window_draw(waves[wavenumber]);
        }

        window_drawSum(waves);
        
        window_render();
    }

    return 0;
}


