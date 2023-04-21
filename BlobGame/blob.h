#include <string>
#include <iostream>

class blob {
    public:
        // constructor
        blob(char);     // char for passing color of blob

        void setAlive(bool);
        void setXCoord(int);
        void setYCoord(int);
        void setColor(char);

        int getXCoord() const;
        int getYCoord() const;
        int getHealth() const;
        int getPower() const;
        bool getStatus() const;
        char getColor() const;
        int getCode() const;
        std::string getName() const;

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void isDead();
        void beingAttack(int);

        // operator overload        
        void operator+(blob&);
        friend std::ostream & operator << (std::ostream &out, const blob &p);

    private:
        
        int health;
        bool isAlive;
        int power;
        char color;
        int xCoord;
        int yCoord; 
        int code;
        int id;
        std::string name;


};