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
void window_CLEAR()
{
    SDL_SetRenderDrawColor(renderer, CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
    SDL_RenderClear(renderer);
}

void window_AXES()
{
    SDL_SetRenderDrawColor(renderer, AXIS_R, AXIS_G, AXIS_B, AXIS_A);
    SDL_RenderDrawLine(renderer, OFFSET, 0, OFFSET, WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer, OFFSET, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);
}

Uint16 window_POLLEVENT()
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

void window_DRAW(SDL_Point* wave)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLines(renderer, wave, WIDTH);
}

void window_RENDER()
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
