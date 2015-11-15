#include "States.h"

GameOver::GameOver(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton, 
                   int points,
                   Music &music, Speaker &speaker,
                   char option)
{
    int scores[10];
    int currentScore;
    
    bool isWinner = false;
        
    FILE *fp = fopen("/sd/mydir/highscores.txt", "r");
    if(fp == NULL) {
        error("Could not open file for read.\n");
    }
    
    for(int i = 0; i < 10; ++i)
    {
        fscanf(fp,"%d", &currentScore);
        fgetc(fp);
        scores[i] = currentScore;
    }
    
    fclose(fp);
        
    uLCD.cls();
    uLCD.textbackground_color(BLACK);
    uLCD.color(WHITE);
    uLCD.printf("\n     Game Over       \n");
    uLCD.printf("     Score: %d\n", points);     
    
    int note = 1;
    
    if (option == 'u')
    {
        uLCD.locate(2, 7);
        uLCD.printf("Normal");
        for(int i = 0; i < 5; ++i)
        {
            if(points > scores[i])
            {
                isWinner = true;
                for (int j = 4; j > i; --j)
                {
                    scores[j] = scores[j-1];
                }
                scores[i] = points;
                break;
            }
        }
    }
    else if (option == 'm')
    {
        uLCD.locate(2, 7);
        uLCD.printf("Crazy");
        for(int i = 5; i < 10; ++i)
        {
            if(points > scores[i])
            {
                isWinner = true;
                for (int j = 9; j > i; --j)
                {
                    scores[j] = scores[j-1];
                }
                scores[i] = points;
                break;
            }
        }
    }
    
    FILE *fp1 = fopen("/sd/mydir/highscores.txt", "w");
    if(fp1 == NULL) 
    {
        error("Could not open file for read.\n");
    }
    
    for(int i = 0; i < 10; ++i)
    {
        fprintf(fp1, "%d\n", scores[i]);
    }
    fclose(fp1);
    
    if(option == 'u')
    {
        for(int i = 0; i < 5; ++i)
        {
            uLCD.locate(5, i+8);
            uLCD.printf("%d:     %d", i+1, scores[i]);
        }
    }
    else if(option == 'm')
    {
        for(int i = 5; i < 10; ++i)
        {
        uLCD.locate(5, i+3);
        uLCD.printf("%d:     %d", i-4, scores[i]);
        }
    }
    
    if(isWinner)
    {
        uLCD.locate(0, 5);
        uLCD.printf(" A WINNER IS YOU!! \n");
        
        while(upButton && downButton && leftButton && rightButton)
        {
            music.playGameOver(speaker, note);
            ++note;
        }
    }
    else
    {      
        uLCD.locate(0, 5);
        uLCD.printf("     YOU SUCK!   \n");
        
        while(upButton && downButton && leftButton && rightButton)
        {
            music.playLoser(speaker, note);
            ++note;
        }
    }
}