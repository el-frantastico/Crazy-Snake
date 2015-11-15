#include "States.h"

////////////////////////////////////////////////////////////////
// CONSTRUCTORS
////////////////////////////////////////////////////////////////
Gameplay::Gameplay(uLCD_4DGL &uLCD)
{   
    uLCD.cls();
    //random seed setup
    srand(time(NULL));   
    
    //LCD setup
    uLCD.background_color(BLACK);
    uLCD.color(BLACK);
    uLCD.set_font(FONT_7X8);
    uLCD.textbackground_color(WHITE);
    
    //border setup
    uLCD.filled_rectangle(  0,   0, 127,  10, WHITE);    // Top Border
    uLCD.filled_rectangle(  0,   0,   3, 127, WHITE);    // Left Border
    uLCD.filled_rectangle(124,   0, 127, 127, WHITE);    // Right Border
    uLCD.filled_rectangle(  0, 126, 127, 127, WHITE);    // Bottom Border
    
    //food setup
    setFoodEaten(true);
    
    //points setup
    setPoints(0);
    uLCD.locate(9, 0);
    uLCD.color(BLACK);
    uLCD.printf("Score: %d", getPoints());
    
    //draw initial snake
    drawHead(snake, uLCD);                           
    for(int i = 1; i < snake.getSize() - 1; ++i)
    {
        snake.setXLocation(i, snake.getXLocation(i-1));
        snake.setYLocation(i, snake.getYLocation(i-1)-5);
               
        uLCD.filled_rectangle(snake.getXLocation(i),
                              snake.getYLocation(i),
                              snake.getXLocation(i)+4,
                              snake.getYLocation(i)+4,
                              GREEN);
    }
}

////////////////////////////////////////////////////////////////
// GET FUNCTIONS
////////////////////////////////////////////////////////////////
bool Gameplay::getFoodEaten()
{
    return FoodEaten;
}

int Gameplay::getFoodLocation(int index)
{
    return FoodLocation[index];
}

int Gameplay::getPoints()
{
    return Points;
}

////////////////////////////////////////////////////////////////
// SET FUNCTIONS
////////////////////////////////////////////////////////////////
void Gameplay::setFoodEaten(bool hasFoodBeenEaten)
{
    FoodEaten = hasFoodBeenEaten;    
}

void Gameplay::setFoodLocation(int LocationX, int LocationY)
{
    FoodLocation[0] = LocationX;
    FoodLocation[1] = LocationY;
}

void Gameplay::setPoints(int points)
{
    Points = points;
}

////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////
void Gameplay::begin(uLCD_4DGL &uLCD, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton)
{
    uLCD.printf("in begin");
    do
    {
        uLCD.printf("in dowhile");
        updateDirection(snake, upButton, downButton, leftButton, rightButton);
        updateLocation(snake, uLCD);
        
        spawnFood(getFoodEaten(), snake, uLCD);
        FoodEaten = eatFood(snake, uLCD);
        
        wait(snake.getSpeed());
        
        rand();
    } while(!wallHit(snake) && !snakeHit(snake));
}
void Gameplay::updateDirection(Snake &snake, PinDetect &upButton, PinDetect &downButton, PinDetect &leftButton, PinDetect &rightButton)
{
    if(!upButton && snake.getDirection() != 's')
    {
        snake.setDirection('n');
    }
    else if(!downButton && snake.getDirection() != 'n')
    {
        snake.setDirection('s');
    }
    else if(!leftButton && snake.getDirection() != 'e')
    {
        snake.setDirection('w');
    }
    else if(!rightButton && snake.getDirection() != 'w')
    {
        snake.setDirection('e');
    }
}

void Gameplay::updateLocation(Snake &snake, uLCD_4DGL &uLCD)
{
    for (int i = snake.getSize() - 1; i > 0; i--)
    {
        snake.setXLocation(i, snake.getXLocation(i-1));
        snake.setYLocation(i, snake.getYLocation(i-1));
    }
    
    switch(snake.getDirection())
    {
        case 'n':
        {
            snake.setYLocation(0, snake.getYLocation(0)-5);
            break;
        }
        case 's':
        {
            snake.setYLocation(0, snake.getYLocation(0)+5);
            break;
        }
        case 'w':
        {
            snake.setXLocation(0, snake.getXLocation(0)-5);
            break;
        }
        case 'e':
        {
            snake.setXLocation(0, snake.getXLocation(0)+5);
            break;
        }
    }
    
    drawHead(snake, uLCD);                      
    eraseTail(snake, uLCD);
}

void Gameplay::drawHead(const Snake snake, uLCD_4DGL &uLCD)
{
    uLCD.filled_rectangle(snake.getXLocation(0),
                          snake.getYLocation(0),
                          snake.getXLocation(0)+4,
                          snake.getYLocation(0)+4,
                          GREEN);
}

void Gameplay::eraseTail(const Snake snake, uLCD_4DGL &uLCD)
{
    uLCD.filled_rectangle(snake.getXLocation(snake.getSize()-1),
                          snake.getYLocation(snake.getSize()-1),
                          snake.getXLocation(snake.getSize()-1)+4,
                          snake.getYLocation(snake.getSize()-1)+4,
                          BLACK);
}

bool Gameplay::wallHit(const Snake snake)
{
    if(snake.getXLocation(0) <= 2)
        return true;
    else if(snake.getXLocation(0)+5 >= 125)
        return true;
    else if(snake.getYLocation(0) <= 9) 
        return true;
    else if(snake.getYLocation(0)+5 >= 127)
        return true;
    else
        return false;
}

bool Gameplay::snakeHit(const Snake snake)
{
    for(int i = 3; i < snake.getSize()-1; ++i)
    {
        if(   snake.getXLocation(0) == snake.getXLocation(i) && snake.getYLocation(0) == snake.getYLocation(i))
            return true;
    }       
    return false;
}
     
void Gameplay::spawnFood(bool foodEaten, const Snake snake, uLCD_4DGL &uLCD)
{
    if(foodEaten)
    {
        
        bool conflict;
        do
        {
            conflict = false;
            
            setFoodLocation(((rand() % 23)*5)+4,   //LocationX
                            ((rand() % 22)*5)+11); //LocationY
            
            for(int i = 0; i < snake.getSize(); ++i)
            {
                if(snake.getXLocation(i) == getFoodLocation(0) && snake.getYLocation(i) == getFoodLocation(1))
                {
                    conflict = true;
                }
            }
        } while(conflict);
    
        uLCD.filled_rectangle(getFoodLocation(0),
                              getFoodLocation(1),
                              getFoodLocation(0)+4,
                              getFoodLocation(1)+4,
                              RED);
    }   
}   

bool Gameplay::eatFood(Snake &snake, uLCD_4DGL &uLCD)
{
    if(snake.getXLocation(0) == getFoodLocation(0) && snake.getYLocation(0) == getFoodLocation(1))
    {
        snake.setSize(snake.getSize()+1); //make snake bigger
        setPoints(getPoints()+1);         //add point
        uLCD.locate(9, 0);
        uLCD.printf("Score: %d", getPoints());
        
        return true;
    }
    else
        return false;
}