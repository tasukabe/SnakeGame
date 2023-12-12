#include "Header/Snake.hpp"

Snake::Snake()
{
}

Snake::~Snake()
{
    this->snake.erase(snake.begin(),snake.end());
}

void Snake::InitSnake(sf::RenderTarget& window)
{
    /**
     * @return void
     * @brief InitSnake
     *  - Initialize bodyPart,
     *  - push_back to snake,
     *  - initialize snake cell texture.
    */
   //*Initialize Snake Texture
    HeadTexture.loadFromFile("../Resource/SnakeTexture/Head.png");
    TailTexture.loadFromFile("../Resource/SnakeTexture/Tail.png");
    BodyTexture.loadFromFile("../Resource/SnakeTexture/Body.png");
    SideTexture.loadFromFile("../Resource/SnakeTexture/Side.png");


   //* Initialize Snake Cells....
    this->bodyPart.cell.setSize(sf::Vector2f(40.f, 40.f));

    this->window_width_inChunk = window.getSize().x / this->bodyPart.cell.getSize().x;
    this->window_height_inChunk = window.getSize().y / this->bodyPart.cell.getSize().y;

    // this->bodyPart.cell.setFillColor(sf::Color::Cyan);

    this->bodyPart.cell.setPosition(
        sf::Vector2f(static_cast<float>((rand() % rand() % window_width_inChunk) * this->bodyPart.cell.getSize().x),
                     static_cast<float>((rand() % rand() % window_height_inChunk) * this->bodyPart.cell.getSize().y))
        );
    
    center = {this->bodyPart.cell.getSize().x / 2.f, this->bodyPart.cell.getSize().y / 2.f};
    
    this->bodyPart.sprite.setOrigin(center);
    
    this->bodyPart.sprite.setPosition(
        this->bodyPart.cell.getPosition().x + center.x,
        this->bodyPart.cell.getPosition().y + center.y
    );

    this->bodyPart.sprite.setTexture(BodyTexture);

    this->snake.push_back(bodyPart);

    //*Set sprite origin center.
    // this->snake[HEAD].sprite.setOrigin(center);

    this->AddBody();
    this->AddBody();

    this->SnakeSize = 2;

    //Initialize Animaion.
    this->Animation = false;

}


void Snake::AddBody()
{
    this->snake.push_back(this->bodyPart);
    SnakeSize += 1;

    this->snake[SnakeSize].cell.setPosition(
        this->snake[SnakeSize - 1].cell.getPosition().x - (this->bodyPart.cell.getSize().x * this->snake[SnakeSize - 1].velocity.x),
        this->snake[SnakeSize - 1].cell.getPosition().y - (this->bodyPart.cell.getSize().y * this->snake[SnakeSize - 1].velocity.y) 
        );
//? Set sprite position.
    this->bodyPart.sprite.setOrigin(center);
    
    this->snake[SnakeSize].sprite.setPosition (
        snake[SnakeSize].cell.getPosition().x + center.x,
        snake[SnakeSize].cell.getPosition().y + center.y
    );

    //* Updating new cell velocity...
    /// @brief the default velocity is not okey to use.
    this->snake[SnakeSize].velocity.x = this->snake[SnakeSize - 1].velocity.x;
    this->snake[SnakeSize].velocity.y = this->snake[SnakeSize - 1].velocity.y;

    this->UpdateSprites();
}

std::vector<SnakeMod> Snake::GetSnake()
{
    return this->snake;
}

void Snake::UpdateSnakeVelocity(const float x, const float y)
{
    this->snake[HEAD].velocity.x = x;
    this->snake[HEAD].velocity.y = y;
}

sf::Vector2f Snake::GetSnakeVelocity() const
{
    return this->snake[HEAD].velocity;
}

const bool Snake::isEaten(sf::RectangleShape food) const
{
    sf::Vector2f foodPosition = food.getPosition();
    if(this->snake[HEAD].cell.getGlobalBounds().contains(foodPosition))
        return true;
    else
        return false;
}

const bool Snake::isSelfCollision() const
{
    for(int i = 1; i <= this->SnakeSize; i++)
    {
        if(this->snake[i].cell.getGlobalBounds().contains(this->snake[HEAD].cell.getPosition()))
            return true;
    }
    return false;
}


void Snake::UpdateSnake()
{
/**
 * @paragraph UpdateSnake()
 * - Set the head new position.
 * - Set all the body parts positon.
*/
    if(!Animation)
    {
        Animation = true;
    } else {
        Animation = false;
    }
    //* Clear previous tail.
    this->snake.pop_back();

    //* Create new cell position according to snake head previous position.
    this->bodyPart.cell.setPosition(
        this->snake[HEAD].cell.getPosition().x + (this->snake[HEAD].cell.getSize().x * this->snake[HEAD].velocity.x),
        this->snake[HEAD].cell.getPosition().y + (this->snake[HEAD].cell.getSize().y * this->snake[HEAD].velocity.y)
    );

    //* Set the sprite top of the cell by adding sprite origins distance from the local Vec2(0, 0)
    this->bodyPart.sprite.setPosition(
        this->snake[HEAD].cell.getPosition().x + center.x, 
        this->snake[HEAD].cell.getPosition().y + center.y
    );

    //* Set new bodypart velocity to head.velocity
    this->bodyPart.velocity = this->snake[HEAD].velocity;
    this->bodyPart.sprite.setTexture(*this->snake[HEAD].sprite.getTexture());

    //* Insert new bodypart at the begining of the snake array.
    this->snake.insert(this->snake.begin(), this->bodyPart);
    
    //* Lastly, Update necessity the sprites.
    this->UpdateSprites();

    if(Animation)
        this->UpdateBodySpriteAnimation();
    
}

void Snake::UpdateSprites()
{
    /**
     * @brief update snake sprites based on
     *  - Rotate head sprite
     *  - [i-1] & [i+1] cell
     *  - Rotate Sprites based ov velocityes
     *  - Rotate Tail sprite
    */
   //* Update Head sprite....
    this->snake[HEAD].sprite.setTexture(this->HeadTexture);

    //* Update Head sprite rotation acording to its velocity.
    this->RotateSprite(HEAD);

    //* Update Tail Sprite....
    this->snake[SnakeSize].sprite.setTexture(this->TailTexture);
    this->RotateSprite(SnakeSize);

    //* Set bodypart texture.
    if(this->snake[HEAD].velocity != this->snake[2].velocity)
    {
        this->snake[1].sprite.setTexture(this->SideTexture);
        this->RotateSideSprite(1);

    }
    else {
        this->snake[1].sprite.setTexture(this->BodyTexture);
        this->RotateSprite(1);
    }

    
    if(this->snake[SnakeSize -1].sprite.getTexture()->getNativeHandle() == this->TailTexture.getNativeHandle())
    {
        this->snake[SnakeSize -1].sprite.setTexture(this->BodyTexture);
    }



    
}

void Snake::UpdateBodySpriteAnimation()
{
    for(int i = 1; i < this->snake.size(); i++){
        if(this->snake[i+1].velocity != this->snake[i-1].velocity && i != SnakeSize){
            //* Is i in side-changing-cell or not and
            //* Cheak i is in range of snake size.
            break;
        }
        if((i%2)){
            //* If i is not even, then change the orientation of it. 
            //* This will make a wavey look of snake body.
            //* UpdateBody Body-Sprite by make it merror in only Y-AXIS.
            this->snake[i].sprite.setScale(1.f, -1.f);
        }
    }
}

void Snake::RotateSprite(const int location)
{
    if(this->snake[location].velocity.x == 1.f )
        this->snake[location].sprite.setRotation(0.f);

    else if(this->snake[location].velocity.x == -1.f )
        this->snake[location].sprite.setRotation(180.f);
   
    else if(this->snake[location].velocity.y == 1.f )
        this->snake[location].sprite.setRotation(90.f);
   
    else if(this->snake[location].velocity.y == -1.f)
        this->snake[location].sprite.setRotation(-90.f);
}

void Snake::RotateSideSprite(const int location)
{
    const int H = location - 1;
    const int P = location + 1;
    //* State 1................................
    if (
        ( (snake[H].velocity.x == 0.f && snake[H].velocity.y == -1.f) && (snake[P].velocity.x == 1.f && snake[P].velocity.y == 0.f) )
        ||
        ( (snake[H].velocity.x == -1.f && snake[H].velocity.y == 0) && (snake[P].velocity.x == 0.f && snake[P].velocity.y == 1.f) )
    )
    { 
            this->snake[location].sprite.setRotation(0.f);
    }
    //* State 2.................................
    else if ( 
        ( (snake[H].velocity.x == 0.f && snake[H].velocity.y == -1.f) 
        && (snake[P].velocity.x == -1.f && snake[P].velocity.y == 0.f) )
        ||
        ( (snake[H].velocity.x == 1.f && snake[H].velocity.y == 0.f) 
        && (snake[P].velocity.x == 0.f && snake[P].velocity.y == 1.f) )
    )
    { 
            this->snake[location].sprite.setRotation(90.f);
    }
    
    //* State 3.................................
    else if (
        ( (snake[H].velocity.x == 1.f && snake[H].velocity.y == 0.f) 
        && (snake[P].velocity.x == 0.f && snake[P].velocity.y == -1.f) )
        ||
        ( (snake[H].velocity.x == 0.f && snake[H].velocity.y == 1.f) 
        && (snake[P].velocity.x == -1.f && snake[P].velocity.y == 0.f) )
    )
    { 
            this->snake[location].sprite.setRotation(180.f);
    }
    //* State 4.................................
    else if (
        ( (snake[H].velocity.x == 0.f && snake[H].velocity.y == 1.f) 
        && (snake[P].velocity.x == 1.f && snake[P].velocity.y == 0.f) )
        ||
        ( (snake[H].velocity.x == -1.f && snake[H].velocity.y == 0.f) 
        && (snake[P].velocity.x == 0.f && snake[P].velocity.y == -1.f) )
    )
    {
            this->snake[location].sprite.setRotation(-90.f);
    }
}

void Snake::isWindowCollision(sf::RenderTarget& window)
{
    if (this->snake[HEAD].cell.getPosition().x >= window.getSize().x )
    {
        this->snake[HEAD].cell.setPosition(sf::Vector2f(0, this->snake[HEAD].cell.getPosition().y));
    }
    else if (this->snake[HEAD].cell.getPosition().x < 0)
    {
        this->snake[HEAD].cell.setPosition(sf::Vector2f(window.getSize().x - this->snake[HEAD].cell.getSize().x,
                                                        this->snake[HEAD].cell.getPosition().y));
    }
    else if (this->snake[HEAD].cell.getPosition().y >= window.getSize().y )
    {
        this->snake[HEAD].cell.setPosition(sf::Vector2f(this->snake[HEAD].cell.getPosition().x, 0));
    }
    else if (this->snake[HEAD].cell.getPosition().y < 0)
    {
        this->snake[HEAD].cell.setPosition(sf::Vector2f(this->snake[HEAD].cell.getPosition().x,
                                                        window.getSize().y - this->snake[HEAD].cell.getSize().y ));
    }
    sf::Vector2f center  = { this->snake[HEAD].cell.getPosition().x + (this->bodyPart.cell.getSize().x / 2.f), 
                            this->snake[HEAD].cell.getPosition().y + (this->bodyPart.cell.getSize().y / 2.f)};

    this->snake[HEAD].sprite.setPosition(center);

    return;
}

void Snake::RenderSnake(sf::RenderTarget& window)
{
    for(SnakeMod& snk : this->snake)
        window.draw(snk.sprite);

    window.draw(this->snake[HEAD].sprite);
}



