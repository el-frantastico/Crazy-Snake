#include "States.h"

Rules::Rules(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton)
{
    uLCD.cls();
    
    //text
    uLCD.color(LGREY);
    uLCD.set_font_size(5, 9);
    uLCD.printf("\n");
    uLCD.printf("  Normal Snake is \n");
    uLCD.printf(" played just like \n");
    uLCD.printf("   the original   \n");
    uLCD.printf(" snake video game.\n");
    uLCD.printf("\n");
    uLCD.printf("    Crazy Snake   \n");
    uLCD.printf(" controls the same\n");
    uLCD.printf("   but its speed  \n");
    uLCD.printf("  varies with the \n"); 
    uLCD.printf("    temperature.  \n");
    uLCD.printf("  The LEDs to the \n");
    uLCD.printf("left of the screen\n");
    uLCD.printf("  show the speed. \n");
    
    while(upButton && downButton && leftButton && rightButton)
    {/*do nothing*/}
}