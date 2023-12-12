#pragma once

#include <SFML/Graphics.hpp>

class GameOver
{
public:

    sf::Texture t_background;
    sf::Texture t_restart;

    sf::Sprite s_background;
    sf::Sprite s_restart;

    GameOver();
    
    void Display(sf::RenderTarget& window);
};

GameOver::GameOver()
{
    //* Initialize everything here.
    if(this->t_background.loadFromFile("../Resource/"));
}

void GameOver::Display(sf::RenderTarget& window)
{
    
}