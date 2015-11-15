#include "thermo.h"
 
TMP36::TMP36(PinName pin) : _pin(pin) {} //This is an initializer list … more to come in class 
// _pin(pin) means pass pin to the AnalogIn constructor 
 
float TMP36::read()
{
//convert sensor reading to temperature in degrees C
    return (_pin.read());
}

//instantiate new class to set p15 to analog input 
//to read and convert TMP36 sensor's voltage output

//TMP36 myTMP36(p15);

//int main()
//{
//    float tempC, tempF;
//
//    while(1) {
//        tempC = myTMP36.read();
//        //convert to degrees F
//        tempF = (9.0*tempC)/5.0 + 32.0;
//        //print current temp
//       uLCD.cls();
//       uLCD.color(BLACK);
//       uLCD.textbackground_color(BLUE);
//       uLCD.printf("%5.2f", tempC);
//       uLCD.textbackground_color(WHITE);
//       uLCD.printf(" C ", WHITE);
//       uLCD.textbackground_color(RED);
//       uLCD.printf("%5.2f", tempF, RED);
//       uLCD.textbackground_color(WHITE);
//       uLCD.printf(" F \n\r", WHITE);
//       wait(.5);
//    }
//}