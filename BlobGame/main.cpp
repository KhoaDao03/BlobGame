/*==========================================================================*/
// Author: Khoa Dao
// Assignment 2
/*==========================================================================*/

//standard header
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "assign2.h"
using namespace std;


/*==========================================================================*/
// constants
const int maxBlobs = 8;
// maximum amount of blobs for the game


/*==========================================================================*/
// function prototypes
void printGrid(blob, blob, blob, blob, blob, blob, blob, blob);
int typeOfFunction();
int askBlob(blob, blob, blob, blob, blob, blob, blob, blob);
void processFunction(int,blob&, int&, blob&, blob&, blob&, blob&, blob&, blob&, blob&, blob&);
blob& getBlob(int, blob&, blob&, blob&, blob&, blob&, blob&, blob&, blob&);
int askDirection();
void processDirection(int, blob&, int&, blob&, blob&, blob&, blob&, blob&, blob&, blob&, blob&);
void pause();
void setTeam(blob&, blob&, blob&, blob&, blob&, blob&, blob&, blob&);
void combinedBlob(int, blob&);

/*==========================================================================*/
/* main function */
int main ()
{   // main function begins
    
    // initialize the 8 blobs for players
    blob one('g');
    blob two('g');
    blob three('g');
    blob four('g');
    blob five('r');
    blob six('r');
    blob seven('r');
    blob eight('r');

    //print intro
    cout << "**************************" << endl;
    cout << "Welcome to Blob the game" << endl;
    cout << "**************************" << endl;
    cout << endl;
    cout << "Rules: " << endl;
    cout << "There are 2 teams with 4 blobs each." << endl;
    cout << "There are only a certain functions availble which can be viewed in game." << endl;
    cout << "Do you best to be the sole survivor and good luck." << endl;
    cout << "Press enter to continue." <<endl;
    cout << endl;

    // assigning team names
    setTeam(one, two, three, four, five, six, seven, eight);

    // initialize array for initial blob positions
    int gridB[maxBlobs][2];
    const int sizeY = sizeof(gridB) / sizeof(gridB[0]);
    const int sizeX = sizeof(gridB[0]) / sizeof(gridB[0][0]);
    for (int y = 0; y < sizeY; y++){
        for (int x = 0; x < sizeX; x++){
            gridB[y][x]=-1;
        }
    }

    //generate initial blob positions
    int max = 10;       // set the upper bound to generate the random number
    srand(time(0));
    bool sameCoord;     // variable to check for same coordinates
    int temp[2];        // variable for temporary store the coordinates
    // for loop repeat 8 times to create 8 unique coordinates
    for (int a = 0; a < maxBlobs; a++){     
        sameCoord = true;       // set sameCoordinates
        while (sameCoord){
            temp[0] = rand()%max;       // generate random value for X coordinate
            temp[1] = rand()%max;       // generate random value for Y coordinate
            for (int i = 0; i< maxBlobs; i++){  // loop inside the list for same coordinates
                if (gridB[i][0] == temp[0] && gridB[i][1] == temp[1]){
                    break;      // if found break out of the loop
                }
                if (i==7) {     // if not, add into the coordinate lists
                    gridB[a][0] = temp[0];  // add value
                    gridB[a][1] = temp[1];  // add value
                    sameCoord = false;      // set sameCoord to false to break out of the loop
                }
            }
        }
        
    }// end for loop

    //set the blob coordinates from the lists
    one.setXCoord(gridB[0][0]);     one.setYCoord(gridB[0][1]);
    two.setXCoord(gridB[1][0]);     two.setYCoord(gridB[1][1]);
    three.setXCoord(gridB[2][0]);   three.setYCoord(gridB[2][1]);
    four.setXCoord(gridB[3][0]);    four.setYCoord(gridB[3][1]);
    five.setXCoord(gridB[4][0]);    five.setYCoord(gridB[4][1]);
    six.setXCoord(gridB[5][0]);     six.setYCoord(gridB[5][1]);
    seven.setXCoord(gridB[6][0]);   seven.setYCoord(gridB[6][1]);
    eight.setXCoord(gridB[7][0]);   eight.setYCoord(gridB[7][1]);


    //print out the grid
    printGrid(one,two,three,four,five,six,seven,eight);
    
    int t = 0;      // initialize turn variables
    //operate the game
    while (true){

    cout << endl;   // skip a line

    // check for team conditions
    if(!one.getStatus() && !two.getStatus() && !three.getStatus() && !four.getStatus()){
        cout << "Team " << eight.getColor() << " wins." << endl;
        cout << "Game end." << endl;    // prints out appropriate message
        return (EXIT_SUCCESS);
    }   // if all team one died
    if(!five.getStatus() && !six.getStatus() && !seven.getStatus() && !eight.getStatus()){
        cout << "Team " << one.getColor() << " wins." << endl;
        cout << "Game end." << endl;    // prints out appropriate message
        return (EXIT_SUCCESS);
    }   // if all team two died

    // check for team turn and print out the message
    if (t%2 == 0){
        cout << "It is team " << one.getColor() << "\'s turn." << endl;
    } else {
        cout << "It is team " << eight.getColor() << "\'s turn." << endl;
    }
    
    // ask the player to choose a blob
    blob& chosen = getBlob(askBlob(one, two, three, four, five, six, seven, eight)
    , one, two, three, four, five, six, seven, eight);

    // ask the player for command and process the command
    processFunction(typeOfFunction(), chosen, t, one, two, three, four, five, six, seven, eight);
    
    // pause to let the player read the notifications
    pause();

    // reset the value turn
    if (t%2 == 0){
        t = 0;
    }

    cout << endl;   // skip a line

    }
    return (EXIT_SUCCESS);
}
//main 


/*==========================================================================*/
void printGrid(blob one, blob two, blob three, blob four, blob five, blob six, 
blob seven, blob eight) // all of the blobs in the game
{

    string grid[10][11];        // initialize the 2d array for the grid

    cout << "Grid: " << endl;   // prints out the title

    const int sizeY = sizeof(grid) / sizeof(grid[0]) ;  // calculate the size of grid Y
    const int sizeX = sizeof(grid[0]) / sizeof(grid[0][0]) -1;  // calculate the size of grid X

    // set up the grid by filling empty space with blanks
    for (int y = 0; y < sizeY; y++){
        for (int x = 0; x < sizeX; x++){
            grid [y][x] = "";   // fill blanks
        }
    }
    


    //insert blobs into the grid with their appropriate names
    grid[one.getYCoord()][one.getXCoord()] = one.getName();
    grid[two.getYCoord()][two.getXCoord()] = two.getName();
    grid[three.getYCoord()][three.getXCoord()] = three.getName();
    grid[four.getYCoord()][four.getXCoord()] = four.getName();
    grid[five.getYCoord()][five.getXCoord()] = five.getName();
    grid[six.getYCoord()][six.getXCoord()] = six.getName();
    grid[seven.getYCoord()][seven.getXCoord()] = seven.getName();
    grid[eight.getYCoord()][eight.getXCoord()] = eight.getName();
    
    // print out the label for x coordinates
    for (int i = 0; i < sizeX+1; i++){
        cout << setw(7) << i << setw(7);    // prints out the x coordinates
    }

    // prints out the grid
    cout << endl << endl;   // skip line to easier to read 
    for (int y = 0; y < sizeY; y++){
        cout << y+1;    // print out the label for y coordinates
        for (int x = 0; x < sizeX; x++){
            if (grid [y][x] == ""){
                grid [y][x] = "**";     // fill the empty space with asterisks
            }
            cout << setw(7) <<grid[y][x] << setw(7);
        }
        cout << endl << endl << endl; // skip line to easier to read 
    }
}
// This function will print out the grid along with the blobs on the grid appropriately





/*==========================================================================*/
int typeOfFunction(){     
    int num;    // variable to store value
    while (true) {
        // prints out the available commands
        cout << endl << endl;
        cout << "Available functions are:" << endl;
        cout << "1. Review the grid" << endl;
        cout << "2. View stats of blobs" << endl;
        cout << "3. Move, attack and combined (depending on the move)." << endl;
        cout << "If you want to change the blob, use the review grid function" << endl;
        cout << "Choose 1,2,3,4 or -1 to quit the program" << endl;
        cin >> num;     // ask for user input
        if (num == 1 || num == 2 || num == 3){
            return num;     // return user input
        } else if (num == -1) {
            exit(EXIT_FAILURE);     // quit the program
        }
        else
        {
            // prompt the user about invalid input and repeat
            cout << "Input is invalid." << endl;
            cout << "Please try again" << endl << endl;
            
            cin.clear();
            cin.ignore(1000,'\n');
            // clear the input stream
        }
    }
}
//This function will identify what kind of function/command the user want to interact
//to the blob/program.





/*==========================================================================*/
void processFunction(int type, blob& c, int& turn, blob& one, blob& two, 
blob& three, blob& four, blob& five, blob& six, blob& seven, blob& eight)
// takes in command type, chosen blobs, current turn, and the 8 blobs
{
    
    if (type == 1){

        printGrid(one,two,three,four,five,six,seven,eight);     // prints out the grid again

    } else if (type == 2){

        cout << c;      // prints out the statistics of blobs

    } else if (type == 3){

        // check for blob's code match with curren turn
        if (c.getCode() == turn%2 ){
            // if correct turn
            if (c.getStatus())  // check for blob's status
            {
            // if alive
            processDirection(askDirection(),c, turn, one, two, three, four, five, six, seven, eight);
            } else {
                // if dead 
                // prompt the user 
                cout << "The blob is dead." << endl;
                cout << "Please choose a different blob or command." << endl;
            }
        } else {
            // if invalid turn
            // prompt the user
            cout << "It is not this blob turn to move. " << endl;
            cout << "Please choose a different blob or command." << endl; 
        }
    }
}
//This function will process the user input for a correct command




/*==========================================================================*/
int askBlob(blob one, blob two, blob three, blob four, blob five, blob six, blob seven, blob eight)
// takes in all the 8 blobs
{
    int num;    // variable to store user input
    while (true) {

        // prompt user about the options for blobs
        cout << endl;
        cout << "Choose the blob to interact:" << endl;
        cout << "1. " << one.getName() << endl;
        cout << "2. " << two.getName() << endl;
        cout << "3. " << three.getName() << endl;
        cout << "4. " << four.getName() << endl;
        cout << "5. " << five.getName() << endl;
        cout << "6. " << six.getName() << endl;
        cout << "7. " << seven.getName() << endl;
        cout << "8. " << eight.getName() << endl;
        cout << "Choose 1,2,3,4,5,6,7,8 or -1 to quit the program" << endl;
        cin >> num;     // ask for user input

        // if the input within range
        if (num < 9 && num > 0){
            return num;     // return the value
        } else if (num == -1) {     // if -1
            exit(EXIT_FAILURE);     // quit the program
        }
        else
        {
            // prompt the user to enter again
            cout << "Input is invalid." << endl;
            cout << "Please try again" << endl << endl;

            // clear the input stream
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }
}
//This function will identify what kind of function the user want to interact
//to the line





/*==========================================================================*/
blob& getBlob(int i, blob& one, blob& two, blob& three, blob& four, blob& five, blob& six, 
blob& seven, blob& eight)
// takes in user input and all of the 8 blobs
{
    if (i == 1){

        return one;

    } else if (i == 2){

        return two;

    } else if (i == 3){

        return three;
        
    } else if (i == 4){

        return four;

    }  else if (i == 5){

        return five;

    }  else if (i == 6){

        return six;

    }  else if (i == 7){
    
        return seven;
        
    }  else if (i == 8){

        return eight;

    }
}
// return the object blob accordingly from the user input






/*==========================================================================*/
int askDirection(){
    int num;
    while (true) {

        // prompt the user about available commands
        cout << endl << endl;
        cout << "Available movements are:" << endl;
        cout << "1. Up" << endl;
        cout << "2. Right" << endl;
        cout << "3. Down" << endl;
        cout << "4. Left" << endl;
        cout << "Choose 1,2,3 or -1 to quit the program" << endl;
        cin >> num;
        if (num == 1 || num == 2 || num == 3 || num == 4){
            return num;
        } else if (num == -1) {
            exit(EXIT_FAILURE);
        }
        else
        {
            cout << "Input is invalid." << endl;
            cout << "Please try again" << endl << endl;
            
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }
}
// This function will identify what kind of function the user want to interact
// to the line





/*==========================================================================*/
void processDirection(int type, blob& c, int& turn, blob& one, blob& two,
blob& three, blob& four, blob& five, blob& six, blob& seven, blob& eight)
// takes in direction, chosen blob, current turn, all the 8 blobs
{

    // arrays of the x coordinates of 8 blobs
    int blobX[8] = {one.getXCoord(),two.getXCoord(),three.getXCoord(),
    four.getXCoord(),five.getXCoord(),six.getXCoord(),seven.getXCoord()
    ,eight.getXCoord()};

    // array of the y coordinates of 8 blobs
    int blobY[8] = {one.getYCoord(),two.getYCoord(),three.getYCoord(),
    four.getYCoord(),five.getYCoord(),six.getYCoord(),seven.getYCoord()
    ,eight.getYCoord()};


    bool exists = false;    // initialize exists and set to false 
    bool sameTeam = true;   // initialize sameTeam and set to true
    int temp = -1;          // set temprorary value to -1

    if (type == 1){     // if input 1 = up

        // check for out of bound
        if (c.getYCoord() - 1 < 0 || c.getYCoord() - 1 > 9){
            cout << "Out of bound. Please try again." << endl;  
            // prompt the user
        } else {
        
            // check for other blob present
            for (int z = 0; z< 8; z++){
                if (blobY[z] == c.getYCoord() - 1 
                && blobX[z] == c.getXCoord()){
                    temp = z+1;     // store the int of the blob
                    exists = true;  // set exists to true
                    
                    // check for same team or different team
                    if (c.getCode() == getBlob(temp, one, two, three, four, five, six, seven, eight).getCode()){
                        sameTeam = true;
                    } else {
                        sameTeam = false;
                    }
                    break;  // break out of the loop
                }
            }
            turn ++;    // change turn to other team
            if (exists){    // if there is another blob
                if (sameTeam){  // if other blob is the same team

                    // combined the two blobs and keep the chosen blob 
                    c + getBlob(temp, one, two, three, four, five, six, seven, eight);
                    c.moveUp();     // move the blob to the position

                    // prompt the user 
                    cout << endl;
                    cout << "Blob " << c.getName() << " absorbed/combined blob "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;

                } else {    // not same team
                    
                    // obtain the blob from the int value
                    blob& t = getBlob(temp, one, two, three, four, five, six, seven, eight);
                    t.beingAttack(c.getPower());    // attack the enemy blob
                    
                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " attacked "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;

                    // when other blob died
                    if (getBlob(temp, one, two, three, four, five, six, seven, eight).getHealth() <= 0){
                        c.moveUp(); // move blob

                        // prompt the user
                        cout << "Blob " 
                        <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                        << " died." << endl;

                    }
                }
            } else {
                c.moveUp();  
                // move blob
            }
        }
        
        

    } else if (type == 2){  // if input 2 = right

        // check for out of bound
        if (c.getXCoord() + 1 < 0 || c.getXCoord() + 1 > 9){
            cout << "Out of bound. Please try again." << endl;
        } else {
        
            // check for other blob present
            for (int z = 0; z < 8; z++){
                if (blobY[z] == c.getYCoord() 
                && blobX[z] == c.getXCoord() + 1){
                    temp = z+1;     // store the int of the blob
                    exists = true;  // set exists to true
                    
                    // check for same team or different team
                    if (c.getCode() == getBlob(temp, one, two, three, four, five, six, seven, eight).getCode()){
                        sameTeam = true;
                    } else {
                        sameTeam = false;
                    }
                    break;  // break out of loop
                }
            }
            
            turn ++;    // change turn to other team
            if (exists){    // if there is another blob
                if (sameTeam){     // if the other blob same team

                    // combined the two blobs and keep the chosen blob 
                    c + getBlob(temp, one, two, three, four, five, six, seven, eight);
                    c.moveRight();

                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " absorbed/combined blob "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;

                } else {    // not same team

                    // obtain the blob from the int value
                    blob& t = getBlob(temp, one, two, three, four, five, six, seven, eight);
                    t.beingAttack(c.getPower());    // attack the enemy blob
                    
                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " attacked "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;
                    
                    // when other blob died
                    if (getBlob(temp, one, two, three, four, five, six, seven, eight).getHealth() <= 0){
                        c.moveUp(); // move blob
                        cout << "Blob " 
                        <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                        << " died." << endl;
                    }
                }
            } else {
                c.moveRight();   
                // move blob
            }
        }


    } else if (type == 3){  // if input 3 = down

        // check for out of bound
        if (c.getYCoord() + 1 < 0 || c.getYCoord() + 1 > 9){
            // prompt user
            cout << "Out of bound. Please try again." << endl;
        } else {
        
            // check for other blob present
            for (int z = 0; z< 8; z++){
                if (blobY[z] == c.getYCoord() + 1 
                && blobX[z] == c.getXCoord()){
                    temp = z+1;     // store the int of blob
                    exists = true;  // set exists to true
                    
                    // check for same team or different team
                    if (c.getCode() == getBlob(temp, one, two, three, four, five, six, seven, eight).getCode()){
                        sameTeam = true;
                    } else {
                        sameTeam = false;
                    }
                    break;  // break out of the loop
                }
            }
            turn ++;    // change turn to other team
            if (exists){    // if there is another blob
                if (sameTeam){  // if other blob same team

                    // combined the two blobs and keep the chosen blob
                    c + getBlob(temp, one, two, three, four, five, six, seven, eight);
                    c.moveDown();   // move the blob to the position

                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " absorbed/combined blob "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;

                } else {    // not same team
                    
                    // obtain the blob from the int value
                    blob& t = getBlob(temp, one, two, three, four, five, six, seven, eight);
                    t.beingAttack(c.getPower());    // attack the enemy blob
                    
                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " attacked "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;
                    
                    // when other blob died
                    if (getBlob(temp, one, two, three, four, five, six, seven, eight).getHealth() <= 0){
                        c.moveUp(); // move blob
                        cout << "Blob " 
                        <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                        << " died." << endl;

                    }
                }
            } else {
                c.moveDown();   
                // move blob
            }
        }
        
    } else if (type == 4){  // if input 4 = right

        // check for out of bound
        if (c.getXCoord() - 1 < 0 || c.getXCoord() - 1 > 9){
            cout << "Out of bound. Please try again." << endl;
        } else {
        
            // check for other blob
            for (int z = 0; z< 8; z++){
                if (blobY[z] == c.getYCoord() 
                && blobX[z] == c.getXCoord() - 1){
                    temp = z+1;     // store the int of the blob
                    exists = true;  // set exists to true
                    
                    // check for same team or different team
                    if (c.getCode() == getBlob(temp, one, two, three, four, five, six, seven, eight).getCode()){
                        sameTeam = true;
                    } else {
                        sameTeam = false;
                    }
                    break;  // break out of loop
                }
            }
            turn ++;    // change turn to other team
            if (exists){    // if there is another blob
                if (sameTeam){  // if the other blob same team

                    // combined the two blobs and keep the chosen blob
                    c + getBlob(temp, one, two, three, four, five, six, seven, eight);
                    c.moveLeft();

                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " absorbed/combined blob "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;

                } else {    // not same team
                    
                    // obtain the blob from the int value
                    blob& t = getBlob(temp, one, two, three, four, five, six, seven, eight);
                    t.beingAttack(c.getPower());    // attack the enemy blob
                    
                    // prompt the user
                    cout << endl;
                    cout << "Blob " << c.getName() << " attacked "
                    <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                    << "." << endl;
                    
                    // when other blob died
                    if (getBlob(temp, one, two, three, four, five, six, seven, eight).getHealth() <= 0){
                        c.moveUp(); // move blob
                        cout << "Blob " 
                        <<  getBlob(temp, one, two, three, four, five, six, seven, eight).getName()
                        << " died." << endl;
                    }
                }
            } else {
                c.moveLeft();   
                // move blob
            }
        }
    } else{
        exit(EXIT_FAILURE);
    }

    // print grid to show changes
    printGrid(one,two,three,four,five,six,seven,eight);


}
//This function will process the user input for a correct command




/*==========================================================================*/
void pause(){
    cout << "press enter to continue...";
    cin.get();
    cin.clear();
    cin.ignore(1000,'\n');
}
// This function allow the user to read the prompts from the program and 
// the grid





/*==========================================================================*/
void setTeam( blob& one, blob& two, blob& three, blob& four, blob& five, blob& six, 
blob& seven, blob& eight)
// takes in all of the 8 blobs
{

    char c1,c2;     // initlize to store user input

    // clear the input stream
    cin.clear();
    cin.ignore(1000,'\n');

    // guide to user to name the teams and blobs
    cout << "Enter the first char of the color you want to set for team 1." << endl;
    cout << "If many characters are involved, only the first one will be used" << endl;
    cin >> c1;
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Enter the first char of the color you want to set for team 1." << endl;
    cout << "If many characters are involved, only the first one will be used" << endl;
    cin >> c2;
    cin.clear();
    cin.ignore(1000,'\n');

    // set the team's color
    one.setColor(c1);
    two.setColor(c1);
    three.setColor(c1);
    four.setColor(c1);

    five.setColor(c2);
    six.setColor(c2);
    seven.setColor(c2);
    eight.setColor(c2);
}
// This function ask the user for team's color/name and set it.


// Notes: This program can be improve by using arrays for blobs
// instead of passing individually. But when I started on it
// I worked with 8 global object variables which has been 
// changed to avoid technical debt.
