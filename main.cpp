#include "States.h"
#include "mbed.h"

//button setup
PinDetect upButton(p28, PullUp);
PinDetect downButton(p26, PullUp);
PinDetect leftButton(p25, PullUp);
PinDetect rightButton(p27, PullUp);

//LCD setup
uLCD_4DGL uLCD(p9, p10, p8); // serial tx, serial rx, reset pin;

//thermometer setup
TMP36 thermo(p18);

//speaker setup
Speaker speaker(p24);

//states enum
enum StateType{MainMenu, HowTo, PlayGame, ALoserIsYou};
StateType state = MainMenu;

//sd setup
SDFileSystem sd(p5, p6, p7, p14, "sd");

//member variables
char option;
int points;
float avgTemp = thermo.read();
Music music;

main()
{
    //LCD setup
    uLCD.display_control(LANDSCAPE);
    uLCD.baudrate(BAUD_3000000); //jack up baud rate to max for fast display   
    uLCD.background_color(BLACK);
    uLCD.cls();
    while(true)
    {
        switch(state)
        {
            case(MainMenu):
            {   
                Startup startup(uLCD, upButton, downButton, leftButton, rightButton);
                startup.scores(uLCD, sd);
                option = startup.select(uLCD, upButton, downButton, leftButton, rightButton, music, speaker);
                if(option == 'u')
                    state =  PlayGame;
                 if(option == 'm')
                    state =  PlayGame;
                if(option == 'd')
                    state = HowTo;
                break;
            }
            case(HowTo):
            {
                Rules rules(uLCD, upButton, downButton, leftButton, rightButton);
                state = MainMenu;
                break;
            }
            case(PlayGame):
            {
                SneakyGameplay gameplay(uLCD, avgTemp);
                gameplay.begin(uLCD, upButton, downButton, leftButton, rightButton, thermo, option, music, speaker);
                points = gameplay.getPoints();
                state = ALoserIsYou;
                break;
            }
            case(ALoserIsYou):
            {
                GameOver gameOver(uLCD, upButton, downButton, leftButton, rightButton, 
                                  points, music, speaker, option);
                state = MainMenu;
                break;
            }
        }//end switch
    }//end while    
}//end main