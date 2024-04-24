#include<window.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;
SDL_Point* tempWave = new SDL_Point[MAX_WIDTH];

//Initialize SDL
void window_INIT(uint32_t window_width, uint32_t window_height)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SignalSim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

//Returns the window size in the addresses of Width and height passed onto it
void window_getsize(uint32_t *window_width, uint32_t *window_height)
{
    SDL_GetWindowSize(window, (int*)window_width, (int*)window_height);
}

//Clear screen each frame
void window_clear()
{
    SDL_SetRenderDrawColor(renderer, CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
    SDL_RenderClear(renderer);
}

//Draw axes
void window_axes(uint32_t window_width, uint32_t window_height)
{
    SDL_SetRenderDrawColor(renderer, AXIS_R, AXIS_G, AXIS_B, AXIS_A);
    SDL_RenderDrawLine(renderer, OFFSET, 0, OFFSET, window_height);
    SDL_RenderDrawLine(renderer, OFFSET, window_height/2, window_width, window_height/2);
}

//Draws scale markers according to the scale in pixels
void window_scale_markers(uint32_t window_width, uint32_t window_height, float x_scale, float y_scale)
{
    SDL_SetRenderDrawColor(renderer, SCALE_R, SCALE_G, SCALE_B, SCALE_A);

        for(uint16_t i = x_scale; i < window_width; i+= x_scale)
            SDL_RenderDrawLine(renderer, OFFSET + i, 0, OFFSET + i, window_height);

        for(uint32_t i = (uint32_t)(window_height/2 + y_scale); i < window_height; i+= y_scale)
            SDL_RenderDrawLine(renderer, OFFSET, i, window_width, i);

        for(int i = (int)(window_height/2 - y_scale); i > 0 ; i-= y_scale)
            SDL_RenderDrawLine(renderer, OFFSET, i, window_width, i);
}

//Polling interrupt, returns a specific number for each button
Uint16 window_pollEvent()
{
    while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return QUIT;
            
            if(event.type == SDL_WINDOWEVENT)
            {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    return REDRAW;
            }

            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        return KEY_UP|REDRAW;
                    case SDLK_DOWN:
                        return KEY_DOWN|REDRAW;
                    case SDLK_LEFT:
                        return KEY_LEFT|REDRAW;
                    case SDLK_RIGHT:
                        return KEY_RIGHT|REDRAW;
                }
            }
        }
    return 0;
}

//Draw all the waves present in the waveTemplate struct array
void window_draw(waveTemplate* waves, uint32_t window_width, uint32_t window_height) 
{
    uint8_t wave_R = 117;
    uint8_t wave_G = 29;
    uint8_t wave_B = 187;
    for (uint16_t wavenumber = 0; wavenumber <= MAX_WAVES; wavenumber++)
    {
        for(uint32_t pixel = 0; pixel < window_width; pixel++)
        {
            tempWave[pixel].y = (waves[wavenumber].points[pixel].y) + window_height/2;
            tempWave[pixel].x = (waves[wavenumber].points[pixel].x) + OFFSET;
        }
        SDL_SetRenderDrawColor(renderer, wave_R, wave_G, wave_B, 255);
        SDL_RenderDrawLines(renderer, tempWave, window_width);
        wave_R += 61;
        wave_G -= 17;
        wave_B += 107;
    }
    
    
}

//Render the current drawing on screen
void window_render()
{
    SDL_RenderPresent(renderer);  
}