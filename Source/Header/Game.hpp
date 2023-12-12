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
/**
 * @brief this codes main priority is frame limit and snake update timer.
 * @note this code dose not support delta time. Though you can include it in the game
 * but this can create more problem due to its vintage buffery look.
 * 
*/

public:
    SnakeGame();
    virtual ~SnakeGame();

    const bool Running() const;
    void PollEvent();
    void Update();
    bool isWin();
    void Render();

    void SetSnakeSpeed(const uint32_t speed) const;

private:
    //*Game Logic
    bool isGameOver;
    bool OnePress;
    bool IsModefiedDeath;

    bool is_win;
    
    sf::Text Text_gameOver;

    //* Data File...
    std::ifstream DataFile_i;
    std::ofstream DataFile_o;

    sf::RectangleShape back;
    // GameOver* game_over;
    //* points...
    float Point;
    float HighScore;
    float HighScore_p;
    float Death = 0;
    float progressRate = 0;
    float p_progressRate = 0;
    void CheakPoints();

    void InitBack();

    sf::Font point_font;
    sf::Text point_text;
    void InitPoint_text();
    void UpdatePoint_text();
    void DeadWindow();
    void ReadFile();
    void WriteFile();

    void Win();
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
