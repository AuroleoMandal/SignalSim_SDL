#include<main.h>
#include<userinput.h>
#include<window.h>
#include<wave.h>

static float x_scale = 100.0f;
static float y_scale = 100.0f;
uint16_t running = 1;

waveTemplate waves[MAX_WAVES+1];

int main(int argc, char* args[])
{
    user_input(waves);


    window_INIT();
    while (running)
    { 
        wave_build(waves, x_scale, y_scale);

        window_clear();

        window_axes();
        
        window_scale_markers(x_scale, y_scale);

        switch(window_pollEvent())
        {
            case QUIT:
                running = 0;
            case KEY_UP:
                y_scale*=1.05;
                break;
            case KEY_DOWN:
                y_scale*=0.95;
                break;
            case KEY_LEFT:
                x_scale*=0.95;
                break;
            case KEY_RIGHT:
                x_scale*=1.05;
                break;
        }

        window_draw(waves);
        
        window_render();
    }

    return 0;
}


