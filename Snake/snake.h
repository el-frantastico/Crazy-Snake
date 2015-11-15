class Snake
{
public:
    Snake();
    Snake(char intitialDirection,
          int initialXLocation = 54,
          int initialYLocation = 54,
          int size = 1,
          float speed = 0.25
          );

    // MEMBER FUNCTIONS
    Snake &operator++();
    void setLocationCoordinates(int index, int xLocation, int yLocation);

    // GET FUNCTIONS
    int getSize() const;
    float getSpeed() const;
    char getDirection() const;
    int getXLocation(int index) const;
    int getYLocation(int index) const;

    // SET FUNCTIONS
    void setSize(int size);
    void setSpeed(float speed);
    void setDirection(char direction);
    void setPreviousDirection(char previousDirection);
    void setXLocation(int index, int location);
    void setYLocation(int index, int location);

private:
    int Size;
    float Speed;
    char Direction;

    int XLocation[600];
    int YLocation[600];
};
