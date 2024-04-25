#include<window.h>

int line_boundingbox = 3;
int mouse_x = 0, mouse_y = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

struct tempWave
{
    SDL_Point* tempPoint = (SDL_Point*)malloc(sizeof(SDL_Point)*MAX_WIDTH);
    uint8_t wave_R, wave_G, wave_B, wave_A;
};typedef struct tempWave tempWave;

tempWave tempWaves[MAX_WAVES+1];


int checkonline(int wavenumber, int pixel);

//Initialize SDL
int window_INIT(uint32_t window_width, uint32_t window_height)
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        fprintf(stderr,"Error initialising SDL: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("SignalSim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return 0;
}

//Returns the window size in the addresses of width and height passed onto it
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

            if(event.type == SDL_MOUSEMOTION)
            {
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                return REDRAW;
            }

            if(event.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y > 0)
                    return MOUSEWHEEL_UP|REDRAW;
                if(event.wheel.y < 0)
                    return MOUSEWHEEL_DOWN|REDRAW;
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
    for (uint16_t wavenumber = 0; wavenumber <= MAX_WAVES; wavenumber++)
    {
        tempWaves[wavenumber].wave_R = 0 + wavenumber * 109;
        tempWaves[wavenumber].wave_G = 90 + wavenumber * 67;
        tempWaves[wavenumber].wave_B = 50 - wavenumber * 217;
        tempWaves[wavenumber].wave_A = 180;
        
        //Discard the topmost bit of RGB value to keep the colour dark
        tempWaves[wavenumber].wave_R &= 0x7f;
        tempWaves[wavenumber].wave_G &= 0x7f;
        tempWaves[wavenumber].wave_B &= 0x7f;

        //Colour the Summation wave differently
        if(wavenumber == MAX_WAVES)
        {
            tempWaves[wavenumber].wave_R = 255;
            tempWaves[wavenumber].wave_G = 255;
            tempWaves[wavenumber].wave_B = 255;
            tempWaves[wavenumber].wave_A = 255;
        }

        for(uint32_t pixel = 0; pixel < window_width; pixel++)
        {
            tempWaves[wavenumber].tempPoint[pixel].y = (waves[wavenumber].points[pixel].y) + window_height/2;
            tempWaves[wavenumber].tempPoint[pixel].x = (waves[wavenumber].points[pixel].x) + OFFSET;

            if(checkonline(wavenumber, pixel))
            {
                tempWaves[wavenumber].wave_R = 255;
                tempWaves[wavenumber].wave_G = 0;
                tempWaves[wavenumber].wave_B = 0;
                tempWaves[wavenumber].wave_A = 255;
            }

        }
        SDL_SetRenderDrawColor(renderer, tempWaves[wavenumber].wave_R, tempWaves[wavenumber].wave_G, tempWaves[wavenumber].wave_B, tempWaves[wavenumber].wave_A);
        SDL_RenderDrawLines(renderer, tempWaves[wavenumber].tempPoint, window_width);
    }
    
    
}

//Render the current drawing on screen
void window_render()
{
    SDL_RenderPresent(renderer);  
}

int checkonline(int wavenumber, int pixel)
{
    int maxX = tempWaves[wavenumber].tempPoint[pixel].x + line_boundingbox;
    int minX = tempWaves[wavenumber].tempPoint[pixel].x - line_boundingbox;
    int maxY = tempWaves[wavenumber].tempPoint[pixel].y + line_boundingbox;
    int minY = tempWaves[wavenumber].tempPoint[pixel].y - line_boundingbox;

    if(mouse_x >= minX && mouse_x <= maxX && mouse_y >= minY && mouse_y <= maxY)
        return 1;
    else
        return 0;
}