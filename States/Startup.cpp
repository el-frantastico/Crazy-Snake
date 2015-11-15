#include "States.h"

Startup::Startup(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton)
{
    uLCD.cls();
    
    //title
    uLCD.locate(3,0);
    uLCD.text_italic(ON);
    uLCD.text_string("Crazy Snake", 3, 1, FONT_12X16, GREEN);
    uLCD.text_italic(OFF);
    uLCD.text_string("Normal Snake",  4, 10, FONT_12X16, WHITE);
    uLCD.text_string("Crazy Snake",   4, 12, FONT_12X16, WHITE);
    uLCD.text_string("Instructions",  4, 14, FONT_12X16, WHITE);
}

char Startup::select(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton, Music &music, Speaker &speaker)
{
    Option = 'u';
    uLCD.filled_circle(15,  83, 5, WHITE);
    int note = 1;
    do
    {
        if(!downButton && Option  == 'u')
        {
            uLCD.filled_circle(15,  83, 5, BLACK);
            uLCD.filled_circle(15,  99, 5, WHITE);
            uLCD.filled_circle(15, 115, 5, BLACK);
            wait(0.2);
            Option = 'm';
        }
        else if(!upButton && Option == 'm' )
        {
            uLCD.filled_circle(15,  83, 5, WHITE);
            uLCD.filled_circle(15,  99, 5, BLACK);
            uLCD.filled_circle(15, 115, 5, BLACK);
            Option = 'u';
        }
        else if(!downButton && Option == 'm' )
        {
            uLCD.filled_circle(15,  83, 5, BLACK);
            uLCD.filled_circle(15,  99, 5, BLACK);
            uLCD.filled_circle(15, 115, 5, WHITE);
            Option = 'd';
        }
        else if(!upButton && Option == 'd' )
        {
            uLCD.filled_circle(15,  83, 5, BLACK);
            uLCD.filled_circle(15,  99, 5, WHITE);
            uLCD.filled_circle(15, 115, 5, BLACK);
            wait(0.2);
            Option = 'm';
        }
        music.playMainMusic(speaker, note);
        ++note;
    } while(leftButton && rightButton);
    
    return Option;
}

void Startup::scores(uLCD_4DGL &uLCD, SDFileSystem &sd)
{
    mkdir("/sd/mydir", 0777);
    FILE *fp = fopen("/sd/mydir/highscores.txt", "r");
    if(fp == NULL) {
        error("Could not open file for read.\n");
    }
    uLCD.set_font(FONT_5X7);
    uLCD.locate(0, 3);
    uLCD.color(BLUE);
    uLCD.printf("Normal");
    uLCD.color(RED);
    uLCD.printf("     Crazy \n");
    
    int currentScore;
    
    uLCD.color(BLUE);
    for(int i = 0; i < 5; ++i)
    {
        fscanf(fp,"%d", &currentScore);
        fgetc(fp);
        uLCD.locate(0, i+4);
        uLCD.printf(" %d: %d", i+1, currentScore);
    }
    
    uLCD.color(RED);
    for(int i = 5; i < 10; ++i)
    {
        fscanf(fp,"%d", &currentScore);
        fgetc(fp);
        uLCD.locate(11, i-1);
        uLCD.printf(" %d: %d", i-4, currentScore);
    }
    
    uLCD.filled_rectangle(52, 24, 72, 71, WHITE);
    
    fclose(fp);
}