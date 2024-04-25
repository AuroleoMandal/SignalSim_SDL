#include<main.h>
#include<userinput.h>
#include<window.h>
#include<wave.h>

static float x_scale = 100.0f;
static float y_scale = 100.0f;
static uint32_t window_height = 640;
static uint32_t window_width = 960;

uint16_t running = 1;

waveTemplate waves[MAX_WAVES+1];

//Calculates and renders the current scene
void drawwindow(void);

int main(int argc, char* args[])
{
    user_input(waves);

    window_INIT(window_width, window_height);

    drawwindow();

    while (running)
    { 
        uint16_t eventID = window_pollEvent();
        
        if(eventID & (KEY_UP|MOUSEWHEEL_UP))
            y_scale*=1.05;

        if(eventID & (KEY_DOWN|MOUSEWHEEL_DOWN))
            y_scale*=0.95;

        if(eventID & (KEY_LEFT|MOUSEWHEEL_DOWN))
            x_scale*=0.95;

        if(eventID & (KEY_RIGHT|MOUSEWHEEL_UP))
            x_scale*=1.05;

        if(eventID & REDRAW)
            drawwindow();

        if(eventID & QUIT)
        {
            SDL_Quit();
            running = 0;
        }
    }

    return 0;
}

void drawwindow()
{
        window_getsize(&window_width, &window_height);

        wave_build(waves, window_width, window_height, x_scale, y_scale);

        window_clear();

        window_scale_markers(window_width, window_height, x_scale, y_scale);

        window_axes(window_width, window_height);

        window_draw(waves, window_width, window_height);

        window_render();
}


