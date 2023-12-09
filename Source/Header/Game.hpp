#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <string>
#include <iomanip>

#include "Snake.hpp"
#include "Food.hpp"
// #include "GameOver.hpp"

typedef struct Owoo
{
    std::string str = "";
    int charSize = 23;
}Owoo;


class SnakeGame
{
public:
    SnakeGame();
    virtual ~SnakeGame();

    const bool Running() const;
    void PollEvent();
    void Update();
    void Render();

    void SetSnakeSpeed(const uint32_t speed) const;

protected:
    //*Game Logic
    bool isGameOver;
    bool OnePress;
    bool IsModefiedDeath;
    
    sf::Text Text_gameOver;

    //* Data File...
    std::ifstream DataFile_i;
    std::ofstream DataFile_o;
    // GameOver* game_over;
    //* points...
    float Point;
    float HighScore;
    float HighScore_p;
    float Death = 0;
    float progressRate = 0;
    float p_progressRate = 0;
    void CheakPoints();

    sf::Font point_font;
    sf::Text point_text;
    void InitPoint_text();
    void UpdatePoint_text();
    void DeadWindow();
    void ReadFile();
    void WriteFile();

    Owoo Owo();

    mutable uint32_t maxTimeSnakeUpdate;
    uint32_t TimeSnakeUpdate;

    int width, height;
    sf::RenderWindow *window;
    sf::Event event;

    //? Snake
    Snake snake;

    //? Food
    Food food;


    void UpdateSnakeAxis();

    void InitVariables();

    void InitWindow();
};
