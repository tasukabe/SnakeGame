#include "Header/Game.hpp"

SnakeGame::SnakeGame()
{
    this->InitWindow();
    this->InitVariables();
}
SnakeGame::~SnakeGame()
{
    delete[] this->window;

    this->WriteFile();
    this->snake.~Snake();
}

const bool SnakeGame::Running() const
{
    return this->window->isOpen();
}



//? Inintialize Window......................................................
void SnakeGame::InitWindow()
{
    /**
     * @return void
     * Make window
     * set position on screen
     */
    this->width = 600;
    this->height = 600;

    this->window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setPosition(sf::Vector2i(600, 200));
    this->window->setFramerateLimit(90);

}

//? Iinitialize Variables..................................................

void SnakeGame::InitVariables()
{
    this->maxTimeSnakeUpdate = 60;
    this->TimeSnakeUpdate = 0;

    this->OnePress = false;

    this->Point = 0;
    this->isGameOver = false;
    this->IsModefiedDeath = false;
    // this->game_over = nullptr;
    this->InitPoint_text();
    this->snake.InitSnake(*this->window);
    this->food.SetPosition(*this->window, this->snake.GetSnake());

    this->Text_gameOver.setFont(this->point_font);
    this->Text_gameOver.setFillColor(sf::Color::Black);
    this->ReadFile();

}

void SnakeGame::DeadWindow()
{
    //? Make a string-stream to load the text to UI.
    std::stringstream GameisGone;

    //? write things to display at the end of the game.
    this->Text_gameOver.setPosition(110.f,170.f);
    this->Text_gameOver.setCharacterSize(60);
    GameisGone<<"!!Game Over!!";

    this->Text_gameOver.setString(GameisGone.str());
    this->window->draw(Text_gameOver);
    GameisGone.str("");

    this->Text_gameOver.setPosition(150.f,Text_gameOver.getPosition().y + 80.f);
    this->Text_gameOver.setCharacterSize(25);

    this->progressRate = Point/(HighScore_p * Death);

    GameisGone
        << "HighScore      : "<<HighScore
        << "\nMyScore       : "<<Point
        << "\nDeath           : "<<Death
        << "\nProgress-Rate : "<<std::fixed <<std::setprecision(3)<<progressRate
        << "\nPrevious-Pro-Rate: "<<std::fixed <<std::setprecision(3)<<p_progressRate;

    Text_gameOver.setString(GameisGone.str());
    this->window->draw(Text_gameOver);

    GameisGone.str("");


    this->Text_gameOver.setCharacterSize(Owo().charSize);
    this->Text_gameOver.setPosition(170.f, Text_gameOver.getPosition().y + 140.f);
    GameisGone<<"\n "<<this->Owo().str;
    this->Text_gameOver.setString(GameisGone.str());
    this->window->draw(Text_gameOver);

    //? load it to the text-stream.
}

void SnakeGame::ReadFile()
{

    this->DataFile_i.open("SavedData");

    if(!this->DataFile_i.is_open())
        {std::cout<<"meh\n";
            return;}


    while (!this->DataFile_i.eof())
    {
        std::string a;
        DataFile_i >> a;

        if(a == "HighScore:")
        {
            DataFile_i >> this->HighScore;
            HighScore_p = HighScore;
        }
        if(a == "Death:")
        {
            int b = 0;
            DataFile_i >>b;
            this->Death += b;
        }

        if(a == "Progress-Rate:")
        {
            DataFile_i >> p_progressRate;
        }
    }
    

    this->DataFile_o.close();
}


//? Write file...........................................................
void SnakeGame::WriteFile()
{
    this->DataFile_o.open("SavedData");
    if(!this->DataFile_o.is_open())
        return;
//* do changes here.
    std::stringstream data;
    data << "HighScore: "<<HighScore<<"\n"
         << "Death: "<<Death <<"\n"
         << "Progress-Rate: "<<std::fixed<<std::setprecision(3)<<progressRate;

    //! don't change it.
    this->DataFile_o.clear();
    this->DataFile_o << data.str();
    this->DataFile_o.close();
}

//? InitPoint.............................................................

void SnakeGame::InitPoint_text()
{
    if(!this->point_font.loadFromFile("../Resource/Fonts/text.ttf"))
    { return; }

    this->point_text.setFont(this->point_font);
    this->point_text.setCharacterSize(25);
    this->point_text.setPosition(sf::Vector2f(40.f, 40.f));
    this->point_text.setColor(sf::Color::Black);
    
}

//? CheakPoints..........................................................

void SnakeGame::CheakPoints()
{
    if(this->HighScore < this->Point)
    {
        this->HighScore = this->Point;
    }
}

//? UpdatePoint..........................................................

void SnakeGame::UpdatePoint_text()
{
    if(!Death)
        this->progressRate = Point/(HighScore_p);
    this->progressRate = Point/(HighScore_p * Death);

    std::stringstream ss;
    ss <<   "MyScore       : "<<Point
       << "\nHighScore      : "<<HighScore
       << "\nDeath           : "<<Death
       << "\nProgress-Rate : "<<std::fixed <<std::setprecision(3)<<progressRate;
    this->point_text.setString(ss.str());
}

//? PollEvent..............................................................

void SnakeGame::PollEvent()
{
    if (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            //? Update Snake-Velocity here...
            this->UpdateSnakeAxis();

            if(this->isGameOver && event.key.code == sf::Keyboard::R)
            {
                this->InitWindow();
                this->InitVariables();
            }
            break;            
        }
    }
}

//? Update Spake Axis......................................................

void SnakeGame::UpdateSnakeAxis()
{
    switch(this->event.key.code)
    {
        case sf::Keyboard::Up:
            if(this->snake.GetSnakeVelocity() == sf::Vector2f(0.f, 1.f) || this->OnePress) { break; }
            this->snake.UpdateSnakeVelocity(0.f, -1.f);
            this->OnePress = true;
            break;
        case sf::Keyboard::Down:
            if(this->snake.GetSnakeVelocity() == sf::Vector2f(0.f, -1.f) || this->OnePress) { break; }
            this->snake.UpdateSnakeVelocity(0.f, 1.f);
            this->OnePress = true;
            break;
        case sf::Keyboard::Left:
            if(this->snake.GetSnakeVelocity() == sf::Vector2f(1.f, 0.f) || this->OnePress) { break; }
            this->snake.UpdateSnakeVelocity(-1.f, 0.f);
            this->OnePress = true;
            break;
        case sf::Keyboard::Right:
            if(this->snake.GetSnakeVelocity() == sf::Vector2f(-1.f, 0.f) || this->OnePress) { break; }
            this->snake.UpdateSnakeVelocity(1.f, 0.f);
            this->OnePress = true;
            break;
    }
}

//? Update..................................................................
void SnakeGame::Update()
{
    PollEvent();

    if(this->isGameOver)
    {
        return;
    }
    this->UpdatePoint_text();
    
    if(this->TimeSnakeUpdate >= this->maxTimeSnakeUpdate)
    {
        this->snake.UpdateSnake();

        this->snake.isWindowCollision(*this->window);

        if(this->snake.isSelfCollision())
            //? @isSelfCollision() is in this condition because if we use it outside of this condition
            //? this function will call 'speed' times what can create a mess into the memory as well as in the game logic.
            this->isGameOver = true;


        this->TimeSnakeUpdate = 0;
        this->OnePress = false;

    }
   this->TimeSnakeUpdate++;
    

    if(this->snake.isEaten(*food.food))
    {
        this->Point++;
        this->food.SetPosition(*this->window, this->snake.GetSnake(), this->food.food->getPosition());

        this->snake.AddBody();
        this->CheakPoints();
    }
        

}

//? Render..................................................................
void SnakeGame::Render()
{
    /**
     * @return void
     * Clear previous window buffer.
     * Draw in buffer.
     * Display the buffer.
     */
    //? Clear previous window buffer.
    this->window->clear(sf::Color(0xf7e796ff));

    //? Render Food.
    this->food.RenderFood(*this->window);

    //? Draw new buffer.
    this->snake.RenderSnake(*this->window);

    if(!this->isGameOver)
        this->window->draw(this->point_text);

   //* Sort everything here...
    if(this->isGameOver)
    {
        sf::RectangleShape back;
        back.setFillColor(sf::Color(0xffffff77));
        back.setSize(sf::Vector2f(this->width, this->height));

        this->window->draw(back);

        if(!this->IsModefiedDeath)
            this->Death += 1;
            this->IsModefiedDeath = true;

        this->DeadWindow();


        this->WriteFile();
        // this->game_over = new GameOver;
        // game_over->Display(*this->window);
    }
    
    //? Display new buffer.
    this->window->display();
}

//? SetSnakeSpeed.....................................................

void SnakeGame::SetSnakeSpeed(const uint32_t speed) const
{
    this->maxTimeSnakeUpdate = speed;
}


//? Owo...............................................................

Owoo SnakeGame::Owo()
{
    //* initialize ajubuju things...
    std::ifstream owo;
    std::vector<std::string> Comment;
    owo.open("Owo.txt");
    int i = 0;
    int charSize = 23;

    //* Read the Owo file...
    while(!owo.eof())
    {
        Comment.push_back("");
        std::getline(owo, Comment.at(i));
        i++;
    }
    owo.close();

/**
 * ! Read before comment anythink about this code below.
 * 
 * * Don't think what hte fuc* is this code.
 * * Why didn't i used loop and mathmetical functions to detarmine the comment section.
 * * If you read the code carefully (what you defenitly not going to do and i also wont recomand you to wais time in it)
 * *                                You can undersnand why I write this logics this fujjy way.
 * * Because this code is more chaotic than my brain.s overthink f(x,...) /* because this my brain not a 2d function ;-)
*/
    if(this->progressRate * 10 > this->p_progressRate && Point >= 14*14){
        i = 0;
        charSize = 30;}
    else if(this->progressRate * 3 > this->p_progressRate && Point >= 14*14/2){
        i = 1;
        charSize = 37;}
    else if (this->progressRate * 2 > this->p_progressRate && Point >= 14*14/6){
        i = 2;
        charSize = 33;}
    else if (this->progressRate  > this->p_progressRate){
        i = 3;
        charSize = 31;}
    else if( this->progressRate + .5f > this->p_progressRate && progressRate +.4f < p_progressRate){
        i = 4;
        charSize = 28;}
    else if( this->progressRate + .9f > this->p_progressRate && progressRate +.5f < p_progressRate){
        i = 5;
        charSize = 29;}
    else {
        i = 6;
        charSize = 32;
    }
    Owoo mew;
    mew.charSize = charSize;
    mew.str = Comment.at(i);
    return mew;
}