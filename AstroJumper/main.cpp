/*--------------------------------------------------------------------------------
* David Badiei
* 06/13/2022
* ICS4U1
* main.cpp
* Main function of AstroJumper, initializes QApplication 
* (provides Qt's functionality), and creates a Game object
*-------------------------------------------------------------------------------*/

#include "Game.h"
#include <QtWidgets/QApplication>

Game* game; //Make game object global so it can be accessed in other parts of the program

/**
 * @param argc Number of command line arguments being passed 
 * @param argv Points to each command line argument passed to the program
 */
int main(int argc, char *argv[])
{
    //Initialize QApplication
    QApplication a(argc, argv);

    //Create and show game class
    game = new Game();
    game->show();

    //Main program loop
    return a.exec();
}
