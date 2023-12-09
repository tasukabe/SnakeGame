#include "Header/Food.hpp"

Food::Food()
{
    food = new sf::RectangleShape;

    food->setSize(sf::Vector2f(40.f, 40.f));
    this->texture.loadFromFile("../Resource/SnakeTexture/Food.png");
    this->sprite.setTexture(texture);
}

Food::~Food()
{
    delete[] this->food;
}



void Food::SetPosition(sf::RenderTarget& window, std::vector<SnakeMod> snake, sf::Vector2f previos_pos)
{
    /**
     * @param window, snake
     * ?divide window into chuncks based on snake.body width and height.
    */
    int chunk_x = window.getSize().x / snake[0].cell.getSize().x;
    int chunk_y = window.getSize().y / snake[0].cell.getSize().y;

    food->setPosition( static_cast<float>((rand() % chunk_x) * snake[0].cell.getSize().x),
                         static_cast<float>((rand() % chunk_y) * snake[0].cell.getSize().y) );
    
    if(previos_pos == food->getPosition())
    {
        //* if it's another time call-back the function so cheak is new food position is changed or not.
        SetPosition(window, snake, this->food->getPosition());
    }

    for(auto& s : snake)
    {
        //? Cheak is food intersecting with Snake Body.
        //? if yes, call this function again to set new position.
        
        if( s.cell.getGlobalBounds().contains(this->food->getPosition()) )
            SetPosition(window, snake, this->food->getPosition());
    
    }
    this->sprite.setPosition(this->food->getPosition());
}


void Food::RenderFood(sf::RenderTarget& window)
{
    window.draw(this->sprite);
}