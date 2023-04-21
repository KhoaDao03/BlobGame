#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include "blob.h"
using namespace std;
const int maxBlobs = 8;

blob::blob(char colo){
    static int numBlobs = 0;
    numBlobs++;
    id = numBlobs;
    
    color = colo;
    health = 100;
    isAlive = true;
    power = 10;

    // set team for blob
    if (numBlobs <= 4){
        code = 0;
    } else {
        code = 1;
    }

    // set up name for blob
    string stemp;
    stringstream t;
    t << id;
    t >> stemp;
    name.push_back(color);
    name += stemp;
    
}


void blob::setAlive(bool alive){
    isAlive = alive;
}
void blob::setXCoord(int xValue){
    xCoord = xValue;
}
void blob::setYCoord(int yValue){
    yCoord = yValue;
}
void blob::setColor(char charVal){
    color = charVal;

    // set/change name for blob
    name = "";
    string stemp;
    stringstream t;
    t << id;
    t >> stemp;
    name.push_back(color);
    name += stemp;
}

int blob::getXCoord() const{
    return xCoord;
}
int blob::getYCoord() const{
    return yCoord;
} 
int blob::getHealth() const{
    return health;
} 
int blob::getPower() const{
    return power;
} 
int blob::getCode() const{
    return code;
} 
char blob::getColor() const{
    return color;
} 
bool blob::getStatus() const{
    return isAlive;
}
string blob::getName() const{
    return name;
} 


void blob::moveUp(){
    yCoord = yCoord - 1;
}
void blob::moveDown(){
    yCoord = yCoord + 1;
}
void blob::moveRight(){
    xCoord = xCoord + 1;
}
void blob::moveLeft(){
    xCoord = xCoord - 1;
}


void blob::operator+(blob& other){
    health += other.getHealth();
    if (power >= other.getPower()){
        power += 2;
    } else {
        power = other.power + 2;
    }
    other.setAlive(0);
    other.setXCoord(10);
}

void blob::beingAttack(int pow){
    health = health - pow;
    if (health <= 0){
        isAlive = false;
        xCoord = 10;
    }
}

void blob::isDead(){
    isAlive = false;
    xCoord = 10;
}



ostream & operator << (ostream &out, const blob &p){
    out << "Name: "<< p.getName() << endl;
    out << "Color: "<< p.getColor() << endl;
    out << "Position: ("<< p.getXCoord() +1 << "," << p.getYCoord() +1 << ")"  << endl;
    out << "Health: "<< p.getHealth() << endl;
    out << "Power: "<< p.getPower() << endl;
    out << "Status (1 means alive): "<< p.getStatus() << endl;
    return out;
}
