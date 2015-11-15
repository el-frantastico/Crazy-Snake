#include "States.h"

SneakyGameplay::SneakyGameplay(uLCD_4DGL &uLCD, const float avgTemp) 
    : Gameplay(uLCD)
{   
    tempThreshold[0] = avgTemp;
    tempThreshold[1] = avgTemp;
    tempThreshold[2] = avgTemp;
    tempThreshold[3] = avgTemp;
    tempThreshold[4] = avgTemp;
    tempThreshold[5] = avgTemp;
    tempThreshold[6] = avgTemp;
    tempThreshold[7] = avgTemp;
    tempThreshold[8] = avgTemp;
    tempThreshold[9] = avgTemp;
}

void SneakyGameplay::begin(uLCD_4DGL &uLCD, 
                           PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton,
                           TMP36 &thermo,
                           char option,
                           Music &music, Speaker &speaker)
{
    srand(thermo.read()*10000);
    
    DigitalOut myLed1(LED1);
    DigitalOut myLed2(LED2);
    DigitalOut myLed3(LED3);
    DigitalOut myLed4(LED4);
    do
    {
        if(option == 'm')
        {
            for (int i = 9; i > 0; i--)
            {   
                tempThreshold[i] = tempThreshold[i-1];
            }
            tempThreshold[0] = thermo.read();
            
            if(thermo.read() < ((tempThreshold[0]+tempThreshold[1]+tempThreshold[2]+tempThreshold[3]+tempThreshold[4]+
                                 tempThreshold[5]+tempThreshold[6]+tempThreshold[7]+tempThreshold[8]+tempThreshold[9])/10))
            {
                myLed1 = 1;
                myLed2 = 0;
                myLed3 = 0;
                myLed4 = 0;
                snake.setSpeed(0.1);
            //    Slomo = true;
            }
            else if(thermo.read() < ((tempThreshold[0]+tempThreshold[1]+tempThreshold[2]+tempThreshold[3]+tempThreshold[4]+
                                      tempThreshold[5]+tempThreshold[6]+tempThreshold[7]+tempThreshold[8]+tempThreshold[9])/10)+0.002)
            {
                myLed1 = 1;
                myLed2 = 1;
                myLed3 = 0;
                myLed4 = 0;
                snake.setSpeed(0.01);
            } 
            else if(thermo.read() > ((tempThreshold[0]+tempThreshold[1]+tempThreshold[2]+tempThreshold[3]+tempThreshold[4]+
                                      tempThreshold[5]+tempThreshold[6]+tempThreshold[7]+tempThreshold[8]+tempThreshold[9])/10)+0.004)
            {
                myLed1 = 1;
                myLed2 = 1;
                myLed3 = 1;
                myLed4 = 1;
                snake.setSpeed(0.0001);
            }                           
            else if(thermo.read() > ((tempThreshold[0]+tempThreshold[1]+tempThreshold[2]+tempThreshold[3]+tempThreshold[4]+
                                      tempThreshold[5]+tempThreshold[6]+tempThreshold[7]+tempThreshold[8]+tempThreshold[9])/10)+0.002)
            {
                myLed1 = 1;
                myLed2 = 1;
                myLed3 = 1;
                myLed4 = 0;
                snake.setSpeed(0.001);
            }
        }
        updateDirection(snake, upButton, downButton, leftButton, rightButton);
        updateLocation(snake, uLCD);
        
        spawnFood(getFoodEaten(), snake, uLCD);
        FoodEaten = eatFood(snake, uLCD, music, speaker);
        
        wait(snake.getSpeed());
        
        rand();
    } while(!wallHit(snake) && !snakeHit(snake));
    music.playDeath(speaker);   
}

bool SneakyGameplay::eatFood(Snake &snake, uLCD_4DGL &uLCD, Music &music, Speaker &speaker)
{
    if(snake.getXLocation(0) == getFoodLocation(0) && snake.getYLocation(0) == getFoodLocation(1))
    {
        music.playChew(speaker);
        snake.setSize(snake.getSize()+1); //make snake bigger
        setPoints(getPoints()+1);         //add point
        uLCD.locate(9, 0);
        uLCD.printf("Score: %d", getPoints());
        
        return true;
    }
    else
        return false;
}