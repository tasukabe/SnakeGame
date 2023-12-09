#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

typedef struct SnakeMod
{
    sf::RectangleShape cell;
    sf::Vector2f velocity = {1.f, 0.f}; //? As default alll of the body part will go on "Right". 
    sf::Sprite sprite;
}SnakeMod;


class Snake
{
    SnakeMod bodyPart;
    unsigned SnakeSize = 0; //! in computer form it is 1("one") 
    unsigned int canBeUpdated = 1;
    
    
    #define HEAD 0
    std::vector<SnakeMod> snake;
    sf::RenderTarget* window;
    
    //* Textures....
    sf::Texture HeadTexture;
    sf::Texture BodyTexture;
    sf::Texture TailTexture;
    sf::Texture SideTexture;

    sf::Vector2f center;

    int window_width_inChunk, window_height_inChunk;

    void RotateSprite(const int location);
    void RotateSideSprite(const int location);

public:

    Snake();
    ~Snake();
    void AddBody();
    void InitSnake(sf::RenderTarget& window);
    void UpdateSnakeVelocity(const float x, const float y);
    void UpdateSnake();
    void UpdateSprites();
    void RenderSnake(sf::RenderTarget& window);
    
    void isWindowCollision(sf::RenderTarget& window);

    const bool isEaten(sf::RectangleShape food) const;
    const bool isSelfCollision() const;

    
    std::vector<SnakeMod> GetSnake();
    sf::Vector2f GetSnakeVelocity() const;

};