#include<main.h>
#include<window.h>
#include<wave.h>

#include<stdio.h> //For troubleshooting

bool running = true;
uint32_t g_scale = 1;
uint32_t f_scale = 1;

float freq = M_PI;


int main(int argc, char* args[])
{
    window_INIT();

    SDL_Point* wave1 = new SDL_Point[WIDTH];
    waveVariables wave1_attr;


    while (running)
    { 
        wave1 = wave_BUILD(wave1, wave1_attr);

        window_CLEAR();
        window_AXES();

        switch(window_POLLEVENT())
        {
            case QUIT:
                running = false;
            case KEY_UP:
                wave_INCREASEY();
                break;
            case KEY_DOWN:
                wave_DECREASEY();
                break;
            case KEY_LEFT:
                wave_DECREASEX();
                break;
            case KEY_RIGHT:
                wave_INCREASEX();
                break;
        }



        // for(int i = 0; i < WIDTH; i++)
        // {
        //     float t = -1*(sin (i*M_PI/x_scale))*y_scale; //multiply with -1 because y-axis is inverted
        //     wave[i].x = i + OFFSET;
        //     wave[i].y = WINDOW_HEIGHT/2 + (int)t;
        // }
        window_DRAW(wave1);
        window_RENDER();
    }

    return 0;
}


