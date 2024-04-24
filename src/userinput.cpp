#include<userinput.h>

uint16_t wavenumber;


/*  void user_defineWave(waveTemplate*)
Asks for user input and modifies waveTemplate->flags(unsigned 16 bit int)
to instruct wave_build()<wave.h> on how to build the wave
*/
void user_defineWaveShape(waveTemplate*);
void user_defineWaveProperties(waveTemplate*);

void user_input(waveTemplate* waves)
{
    printf("The maximum waves you can define are %d\n\n", MAX_WAVES);

    for(wavenumber = 0; wavenumber < MAX_WAVES; wavenumber++)
    {
        user_defineWaveShape(waves);
        user_defineWaveProperties(waves);
    }
}

void user_defineWaveShape(waveTemplate* waves)
{
    waves[wavenumber].flags = 0;

    int type;
    printf("\nWave number %d\
    \nWhat kind of wave would you like?\
    \n1.Sine  2.Square  3.Triangle\n", wavenumber+1);

    scanf(" %d", &type);

    switch(type)
    {
        case(1):
            waves[wavenumber].flags|= SINE;
            break;
        case(2):
            waves[wavenumber].flags|= SQUARE;
            break;
        case(3):
            waves[wavenumber].flags|= TRIANGLE;
            break;
        default:
            printf("Invalid input, please try again\n\n");
            user_defineWaveShape(waves);
    }
}

void user_defineWaveProperties(waveTemplate* waves)
{
    float answer;
    if(waves[wavenumber].flags & SINE)
    {
        printf("Please define frequency (In radians) ");
        scanf(" %f", &answer);
        waves[wavenumber].frequency = answer;

        printf("Please define amplitude ");
        scanf(" %f", &answer);
        waves[wavenumber].amplitude = answer;
    }

    if(waves[wavenumber].flags & SQUARE)
    {
        printf("Please define the duty cycle (0.0 to 1.0) ");
        scanf(" %f", &answer);
        if(answer >= 0 && answer <= 1)
            waves[wavenumber].low_state = answer;
        else
            printf("\nInvalid answer \n");

        printf("Please define the frequency ");
        scanf(" %f", &answer);
        waves[wavenumber].frequency = answer;

        printf("Please define the high state ");
        scanf(" %f", &answer);
        waves[wavenumber].high_state = answer;

        printf("Please define the low state ");
        scanf(" %f", &answer);
        waves[wavenumber].low_state = answer;
    }
}