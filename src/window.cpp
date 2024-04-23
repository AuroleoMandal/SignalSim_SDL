#include<window.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;
SDL_Point* tempWave = new SDL_Point[WIDTH];

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

void window_scale_markers(float x_scale, float y_scale)
{
    SDL_SetRenderDrawColor(renderer, SCALE_R, SCALE_G, SCALE_B, SCALE_A);

        for(int i = x_scale; i < WINDOW_WIDTH; i+= x_scale)
            SDL_RenderDrawLine(renderer, OFFSET + i, 0, OFFSET + i, WINDOW_HEIGHT);

        for(int i = WINDOW_HEIGHT/2 + y_scale; i < WINDOW_HEIGHT; i+= y_scale)
            SDL_RenderDrawLine(renderer, OFFSET, i, WINDOW_WIDTH, i);

        for(int i = WINDOW_HEIGHT/2 - y_scale; i > 0 ; i-= y_scale)
            SDL_RenderDrawLine(renderer, OFFSET, i, WINDOW_WIDTH, i);
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

//Draw all the waves present in the waveTemplate struct array
void window_draw(waveTemplate* waves) 
{
    uint8_t wave_R = 117;
    uint8_t wave_G = 29;
    uint8_t wave_B = 187;
    for (uint16_t wavenumber = 0; wavenumber <= MAX_WAVES; wavenumber++)
    {
        for(uint32_t pixel = 0; pixel < WIDTH; pixel++)
        {
            tempWave[pixel].y = (waves[wavenumber].points[pixel].y) + WINDOW_HEIGHT/2;
            tempWave[pixel].x = (waves[wavenumber].points[pixel].x) + OFFSET;
        }
        SDL_SetRenderDrawColor(renderer, wave_R, wave_G, wave_B, 255);
        SDL_RenderDrawLines(renderer, tempWave, WIDTH);
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