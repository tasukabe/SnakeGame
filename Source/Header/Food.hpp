#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.hpp"

class Food {
    public:
    Food();
    ~Food();
    
    sf::RectangleShape* food;
    sf::Texture texture;
    sf::Sprite sprite;

    void SetPosition(sf::RenderTarget& window, std::vector<SnakeMod> snake,  sf::Vector2f previos_pos = {0.f, 0.f});
    void RenderFood(sf::RenderTarget& window);
};