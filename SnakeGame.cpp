#include "SnakeGame.h"

SnakeGame::SnakeGame()
{
    srand(time(NULL));
    font.loadFromFile("SuperMarioFont.ttf");
    bufferPointSFX.loadFromFile("PointSFX.wav");
    bufferDefeatSFX.loadFromFile("DefeatSFX.wav");

    food.setSize(Vector2f(Snake::BLOCK_SIZE, Snake::BLOCK_SIZE));
    food.setFillColor(Color::Red);

    gameOver = false;
    userRegistered = false;

    loadScore();
}

void SnakeGame::init(size_t w, size_t h, string t)
{
    width = w;
    height = h;
    title = t;

    size_t x = rand() % (w / Snake::BLOCK_SIZE) * Snake::BLOCK_SIZE;
    size_t y = rand() % (h / Snake::BLOCK_SIZE) * Snake::BLOCK_SIZE;
    window.create(VideoMode(w, h), t);

    snake = new Snake(x, y);
    createFood();

    run();
}

void SnakeGame::handleEvents()
{
    Event e;
    while(window.pollEvent(e))
    {
        switch (e.type)
        {
        case Event::Closed:
            window.close();
            break;

        case Event::KeyPressed:
            switch (e.key.code)
            {
            case Keyboard::Up:
                snake->setXDir(0);
                snake->setYDir(-1);
                break;
            case Keyboard::Down:
                snake->setXDir(0);
                snake->setYDir(1);
                break;
            case Keyboard::Left:
                snake->setXDir(-1);
                snake->setYDir(0);
                break;
            case Keyboard::Right:
                snake->setXDir(1);
                snake->setYDir(0);
                break;
            case Keyboard::Escape:
                window.close();
                break;
            case Keyboard::Return:
                if(gameOver==true && theText.getSize()==5)
                {
                    if(userRegistered == false)
                    {
                        saveScore();
                    }
                    userRegistered = true;
                }
                break;
            default:
                break;
            }
            break;

        case Event::TextEntered:
            if(e.text.unicode < 128)
            {
                if(e.text.unicode == 8 && theText.getSize() > 0)
                {
                    theText.erase(theText.getSize() -1, 1);
                }
                else
                {
                    if((theText.getSize() < 5) && (e.text.unicode != 13)) theText += static_cast<char>(e.text.unicode);
                }
            }
            break;

        default:
            break;
        }
    }
}

void SnakeGame::render()
{
    window.clear();

    window.draw(textScore);

    if(gameOver == false)
    {
        vector<RectangleShape> body = snake->getBody();

        for (auto block : snake->getBody())
        {
            window.draw(block);
        }

        window.draw(food);
    }

    if(gameOver == true)
    {
        window.draw(textUser);

        if(userRegistered == true)
        {
            window.draw(titleScores);
            printScores();
        }

    }

    window.display();
}

void SnakeGame::run()
{
    Clock clock;
    while (window.isOpen())
    {
        clock.restart();
        handleEvents();
        update();
        render();

        if (clock.getElapsedTime() < DELAY)
        {
            sleep(DELAY - clock.getElapsedTime());
        }
    }
}

void SnakeGame::update()
{
    snake->setAlpha(alpha--);
    snake->update();

    if (snake->bodyCollision() || snake->frameCollision(width, height) || snake->getAlpha() == 0)
    {
        if(gameOver == false)
        {
            soundDefeatSFX.setBuffer(bufferDefeatSFX);
            soundDefeatSFX.play();
        }

        gameOver = true;
    }

    if (snake->getFront().getPosition() == food.getPosition())
    {
        alpha = 255;
        ++score;
        soundPointSFX.setBuffer(bufferPointSFX);
        soundPointSFX.play();

        createFood();
        snake->grow();
    }

    printNonMobile();
}

void SnakeGame::createFood()
{
    Vector2f foodPosition;

    foodPosition.x = rand() % (width / Snake::BLOCK_SIZE) * Snake::BLOCK_SIZE;
    foodPosition.y = rand() % (height / Snake::BLOCK_SIZE) * Snake::BLOCK_SIZE;

    food.setPosition(foodPosition);
}

void SnakeGame::printNonMobile()
{
    textScore.setFont(font);
    textScore.setCharacterSize(Snake::BLOCK_SIZE*2);
    textScore.setFillColor(Color(255, 255, 255, 150));
    textScore.setOutlineThickness(3);
    textScore.setPosition(10,10);
    textScore.setString("SCORE: " + to_string(score));

    textUser.setFont(font);
    textUser.setCharacterSize(Snake::BLOCK_SIZE*2);
    textUser.setFillColor(Color(255, 255, 255, 150));
    textUser.setOutlineThickness(3);
    textUser.setPosition(10,Snake::BLOCK_SIZE*3);
    textUser.setString("USER: " + theText);

    titleScores.setFont(font);
    titleScores.setCharacterSize(Snake::BLOCK_SIZE*2);
    titleScores.setFillColor(Color(255, 255, 255, 150));
    titleScores.setOutlineThickness(3);
    titleScores.setPosition(600,10);
    titleScores.setString("# | PLAYER | SCORE");
}

void SnakeGame::printScores()
{
    scores.setFont(font);
    scores.setCharacterSize(Snake::BLOCK_SIZE*2);
    scores.setFillColor(Color(255, 255, 255, 150));

    int x = 4;
    int y = 1;
    for(auto item: highScores)
    {
        scores.setPosition(600, Snake::BLOCK_SIZE*x);
        scores.setString(to_string(y) + " | " + item.getUser() + " | " + to_string(item.getScore()));
        window.draw(scores);

        x += 3; ++y;
    }
}

void SnakeGame::saveScore()
{
    u.setUser(theText.toAnsiString());
    u.setScore(score);

    highScores.push_back(u);
    highScores.sort();
    highScores.reverse();

    if(highScores.size()>10)
    {
        highScores.pop_back();
    }

    ofstream write("scores.txt");
    if(write.is_open())
    {
        list <User> :: iterator it;
        for(it=highScores.begin(); it!=highScores.end(); ++it)
        {
            write << *it << endl;
        }
        write.close();
    }
}

void SnakeGame::loadScore()
{
    ifstream read("scores.txt");

    if(read.is_open())
    {
        User u;
        while(read >> u)
        {
            highScores.push_back(u);
        }
        read.close();
    }
}
