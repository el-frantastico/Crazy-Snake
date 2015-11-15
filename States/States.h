#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "thermo.h"
#include "music.h"
#include "SDFileSystem.h"

class Startup
{
public:
    //CONSTRUCTOR
    Startup(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton);
    
    //MEMBER FUNCTIONS
    char select(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton,
                Music &music, Speaker &speaker);
    void scores(uLCD_4DGL &uLCD, SDFileSystem &sd);

private:
    char Option;
};

class Rules
{
public:
    Rules(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton);
};

class Gameplay
{
public:
    // CONSTRUCTOR 
    Gameplay(uLCD_4DGL &uLCD);
   
    // GET FUNCTIONS
    bool getFoodEaten();
    int getFoodLocation(int index);
    int getPoints();
    
    // SET FUNCTIONS
    void setFoodEaten(bool hasFoodBeenEaten);
    void setFoodLocation(int LocationX, int LocationY);
    void setPoints(int points);
    
    //MEMBER FUNCTIONS
    void begin(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton);

protected:    
    void updateDirection(Snake &snake, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton);
    void updateLocation(Snake &snake, uLCD_4DGL &uLCD);
    void drawHead(const Snake snake, uLCD_4DGL &uLCD);
    void eraseTail(const Snake snake, uLCD_4DGL &uLCD);
    bool wallHit(const Snake snake);
    bool snakeHit(const Snake);
    void spawnFood(bool foodEaten, const Snake snake, uLCD_4DGL &uLCD);
    bool eatFood(Snake &snake, uLCD_4DGL &uLCD);
    
    Snake snake;
    bool FoodEaten;
    int FoodLocation[2];
    int Points;
};

class SneakyGameplay : public Gameplay
{
public:
    // CONSTRUCTOR 
    SneakyGameplay(uLCD_4DGL &uLCD, const float avgTemp);

    // MEMBER FUNCTIONS
    void begin(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton, 
               TMP36 &thermo, 
               char option, 
               Music &music, Speaker &speaker);
protected:    
    bool eatFood(Snake &snake, uLCD_4DGL &uLCD, Music &music, Speaker &speaker);

private:
    float tempThreshold[10];
};

class GameOver
{
public:
    //CONSTRUCTOR
    GameOver(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton, 
             int points,
             Music &music, Speaker &speaker,
             char option);   
};