
#include<window.h>
#include <math.h>
#include<stdio.h> //For troubleshooting

bool running = true;
int x_scale = 100;
int y_scale = 100;

SDL_Point* wave = new SDL_Point[WIDTH];

int main(int argc, char* args[])
{
    window_INIT();

    while (running)
    { 
        window_CLEAR();
        window_AXES();
        switch(window_POLLEVENT())
        {
            case QUIT:
                running = false;
            case KEY_UP:
                y_scale++;
                break;
            case KEY_DOWN:
                if(y_scale>5)
                y_scale--;
                break;
            case KEY_LEFT:
                if(x_scale>5)
                x_scale--;
                break;
            case KEY_RIGHT:
                x_scale++;
                break;
        }

        for(int i = 0; i < WIDTH; i++)
        {
            float t = -1*(sin (i*M_PI/x_scale))*y_scale; //multiply with -1 because y-axis is inverted
            wave[i].x = i + OFFSET;
            wave[i].y = WINDOW_HEIGHT/2 + (int)t;
        }
        window_DRAW(wave);
        window_RENDER();
    }

    return 0;
}


