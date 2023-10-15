#include "Menu.h"

int main()
{
    //Init Game
    Menu game;

    //Game loop
    while (game.running()) 
    {
        //Update
        game.update();
        //Render
        game.render();
    }
    return 0;
}