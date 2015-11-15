#include "snake.h"

Snake::Snake()
{
    setDirection('s');

    setSize(5);
    setSpeed(0.05);

    setLocationCoordinates(0, 54, 56);
    for(int i = 1; i < Size - 1; ++i) {
        XLocation[i] = XLocation[i-1];
        YLocation[i] = YLocation[i-1]-6;
    }
}

Snake::Snake(char initialDirection,
             int initialXLocation,
             int initialYLocation,
             int size,
             float speed)
{
    setDirection(initialDirection);

    setSize(size);
    setSpeed(speed);

    setLocationCoordinates(0, initialXLocation, initialYLocation);
    for(int i = 1; i < Size - 1; ++i) {
        XLocation[i] = XLocation[i-1];
        YLocation[i] = YLocation[i-1]-6;
    }
}

// MEMBER FUNCTIONS
Snake &Snake::operator++()
{
    setSize(getSize() + 1);
    return (*this);
}

void Snake::setLocationCoordinates(int index, int xLocation, int yLocation)
{
    setXLocation(index, xLocation);
    setYLocation(index, yLocation);
}



// GET FUNCTIONS
int Snake::getSize() const
{
    return Size;
}

float Snake::getSpeed() const
{
    return Speed;
}

char Snake::getDirection() const
{
    return Direction;
}

int Snake::getXLocation(int index) const
{
    return XLocation[index];
}

int Snake::getYLocation(int index) const
{
    return YLocation[index];
}

// SET FUNCTION
void Snake::setSize(int size)
{
    Size = size;
}

void Snake::setSpeed(float speed)
{
    Speed = speed;
}

void Snake::setDirection(char directionLetter)
{
    Direction = directionLetter;
}

void Snake::setXLocation(int index, int location)
{
    XLocation[index] = location;
}

void Snake::setYLocation(int index, int location)
{
    YLocation[index] = location;
}
