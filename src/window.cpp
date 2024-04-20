#include<window.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;

//Initialize SDL
void window_INIT()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
}

//Clear screen each frame
void window_clear()
{
    SDL_SetRenderDrawColor(renderer, CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
    SDL_RenderClear(renderer);
}

//Draw axes
void window_axes()
{
    SDL_SetRenderDrawColor(renderer, AXIS_R, AXIS_G, AXIS_B, AXIS_A);
    SDL_RenderDrawLine(renderer, OFFSET, 0, OFFSET, WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer, OFFSET, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);
}

void window_scale_markers()
{
    int scale_markers = 5;
    SDL_SetRenderDrawColor(renderer, AXIS_R, AXIS_G, AXIS_B, AXIS_A);
        for(int i = 100; i < WINDOW_WIDTH; i+= 100)
        {
            SDL_RenderDrawLine(renderer, OFFSET + i, (WINDOW_HEIGHT/2)-scale_markers, OFFSET + i, (WINDOW_HEIGHT/2)+scale_markers);
        }
}

//Polling interrupt, returns a specific number for each button
Uint16 window_pollEvent()
{
    while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                return QUIT;
            }
            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        return KEY_UP;
                    case SDLK_DOWN:
                        return KEY_DOWN;
                    case SDLK_LEFT:
                        return KEY_LEFT;
                    case SDLK_RIGHT:
                        return KEY_RIGHT;
                }
            }
        }
    return 0;
}

//Draw whichever wave structure was passed onto it
void window_draw(waveTemplate wave) 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLines(renderer, wave.wavepoint, WIDTH);
}

void window_drawSum(waveTemplate* waves) 
{
    SDL_SetRenderDrawColor(renderer, 255, 200, 200, 255);
    SDL_RenderDrawLines(renderer, waves[MAX_WAVES].wavepoint, WIDTH);
}

//Render the current drawing on screen
void window_render()
{
    SDL_RenderPresent(renderer);  
}



//int scale_markers = 5;
        // for(int i = x_scale; i < WINDOW_WIDTH; i+= x_scale)
        // {
        //     SDL_RenderDrawLine(renderer, OFFSET + i, (WINDOW_HEIGHT/2)-scale_markers, OFFSET + i, (WINDOW_HEIGHT/2)+scale_markers);
        // }
        // for(int i = WINDOW_HEIGHT/2 + y_scale; i < WINDOW_HEIGHT; i+= y_scale)
        // {
        //     SDL_RenderDrawLine(renderer, OFFSET - scale_markers, i, OFFSET + scale_markers, i);
        // }
        // for(int i = WINDOW_HEIGHT/2 - y_scale; i > 0; i-= y_scale)
        // {
        //     SDL_RenderDrawLine(renderer, OFFSET - scale_markers, i, OFFSET + scale_markers, i);
        // }
