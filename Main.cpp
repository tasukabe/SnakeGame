#include "Source/Header/Game.hpp"
#include <random>
#include <iostream>


int main()
{
    srand(time(NULL));
    
    SnakeGame snake_game;

    snake_game.SetSnakeSpeed(17); //! to make high the speed you have to reduce speed!

    while(snake_game.Running())
    {
        snake_game.Update();
        snake_game.Render();
    }

    return 0;
}
