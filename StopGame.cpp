#include "StopGame.h"

StopGame::StopGame()
{
    srand(time(NULL));
    font.loadFromFile("SuperMarioFont.ttf");
    bufferFirstSFX.loadFromFile("PointSFX.wav");
    bufferSecondSFX.loadFromFile("PointSFX.wav");
    bufferThirdSFX.loadFromFile("PointSFX.wav");
    bufferDefeatSFX.loadFromFile("DefeatSFX.wav");
}

void StopGame::init(size_t w, size_t h, string t)
{
    width = w;
    height = h;
    title = t;
    window.create(VideoMode(w, h), t);

    gameOver = false;
    score = 0;

    texture = new Texture();
    texture->loadFromFile("NES - SMB3.png");

    for(int i(0); i<3; ++i)
    {
        fillFirst();
        fillSecond();
        fillThird();
    }

    run();
}

void StopGame::handleEvents()
{
    Event e;
    while (window.pollEvent(e))
    {
        switch (e.type)
        {
        case Event::Closed:
            window.close();
            break;

        case Event::KeyPressed:
            switch (e.key.code)
            {
            case Keyboard::Num1: case Keyboard::A: case Keyboard::Numpad1:
                if(firstRow.front()->getCostume() == Entity::RACOON && gameOver == false)
                {
                    firstRow.pop();
                    fillFirst();
                    ++score;
                    soundFirstSFX.setBuffer(bufferFirstSFX);
                    soundFirstSFX.play();
                }
                else if(firstRow.front()->getCostume() != Entity::RACOON && gameOver == false)
                {
                    soundDefeatSFX.setBuffer(bufferDefeatSFX);
                    soundDefeatSFX.play();
                    gameOver = true;
                }
                break;
            case Keyboard::Num2: case Keyboard::S: case Keyboard::Numpad2:
                if(secondRow.front()->getCostume() == Entity::RACOON && gameOver == false)
                {
                    secondRow.pop();
                    fillSecond();
                    ++score;
                    soundSecondSFX.setBuffer(bufferSecondSFX);
                    soundSecondSFX.play();
                }
                else if(secondRow.front()->getCostume() != Entity::RACOON && gameOver == false)
                {
                    soundDefeatSFX.setBuffer(bufferDefeatSFX);
                    soundDefeatSFX.play();
                    gameOver = true;
                }
                break;
            case Keyboard::Num3: case Keyboard::D: case Keyboard::Numpad3:
                if(thirdRow.front()->getCostume() == Entity::RACOON && gameOver == false)
                {
                    thirdRow.pop();
                    fillThird();
                    ++score;
                    soundThirdSFX.setBuffer(bufferThirdSFX);
                    soundThirdSFX.play();
                }
                else if(thirdRow.front()->getCostume() != Entity::RACOON && gameOver == false)
                {
                    soundDefeatSFX.setBuffer(bufferDefeatSFX);
                    soundDefeatSFX.play();
                    gameOver = true;
                }
                break;
            case Keyboard::Escape:
                window.close();
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}

void StopGame::render()
{
    window.clear();

    if(gameOver == false)
    {
        window.draw(textScore);
        window.draw(textInstructions);
        window.draw(limit);
        window.draw(*firstRow.front()->getSprite());
        window.draw(*secondRow.front()->getSprite());
        window.draw(*thirdRow.front()->getSprite());
    }
    else
    {
        window.draw(textOver);
        window.draw(textFinal);
    }

    window.display();
}

void StopGame::run()
{
    Clock clock;
    while(window.isOpen())
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

void StopGame::update()
{
    if(gameOver == false)
    {
        firstRow.front()->update();
        if (firstRow.front()->getSprite()->getPosition().x > width && firstRow.front()->getCostume() == Entity::FROG)
        {
            firstRow.pop();
            fillFirst();
            ++score;
            soundFirstSFX.setBuffer(bufferFirstSFX);
            soundFirstSFX.play();
        }
        else if (firstRow.front()->getSprite()->getPosition().x > 950 && firstRow.front()->getCostume() != Entity::FROG)
        {
            gameOver = true;
            soundDefeatSFX.setBuffer(bufferDefeatSFX);
            soundDefeatSFX.play();
        }

        secondRow.front()->update();
        if (secondRow.front()->getSprite()->getPosition().x > width && secondRow.front()->getCostume() == Entity::FROG)
        {
            secondRow.pop();
            fillSecond();
            ++score;
            soundSecondSFX.setBuffer(bufferSecondSFX);
            soundSecondSFX.play();
        }
        else if (secondRow.front()->getSprite()->getPosition().x > 950 && secondRow.front()->getCostume() != Entity::FROG)
        {
            gameOver = true;
            soundDefeatSFX.setBuffer(bufferDefeatSFX);
            soundDefeatSFX.play();
        }

        thirdRow.front()->update();
        if (thirdRow.front()->getSprite()->getPosition().x > width && thirdRow.front()->getCostume() == Entity::FROG)
        {
            thirdRow.pop();
            fillThird();
            ++score;
            soundThirdSFX.setBuffer(bufferThirdSFX);
            soundThirdSFX.play();
        }
        else if (thirdRow.front()->getSprite()->getPosition().x > 950 && thirdRow.front()->getCostume() != Entity::FROG)
        {
            gameOver = true;
            soundDefeatSFX.setBuffer(bufferDefeatSFX);
            soundDefeatSFX.play();
        }
    }

    printNonMobile();
}

void StopGame::printNonMobile()
{
    textScore.setFont(font);
    textScore.setCharacterSize(50);
    textScore.setFillColor(Color::White);
    textScore.setOutlineThickness(3);
    textScore.setPosition(10, 10);
    textScore.setString("SCORE: " + to_string(score));

    textInstructions.setFont(font);
    textInstructions.setCharacterSize(50);
    textInstructions.setFillColor(Color::White);
    textInstructions.setOutlineThickness(3);
    textInstructions.setPosition(1000, 300);
    textInstructions.setString("NO\nRACOONS\nALLOWED");

    textFinal.setFont(font);
    textFinal.setCharacterSize(50);
    textFinal.setFillColor(Color::White);
    textFinal.setOutlineThickness(3);
    textFinal.setPosition(50, 200);
    textFinal.setString("FINAL SCORE: " + to_string(score));

    textOver.setFont(font);
    textOver.setCharacterSize(150);
    textOver.setFillColor(Color::White);
    textOver.setOutlineThickness(3);
    textOver.setPosition(50, 10);
    textOver.setString("GAME OVER");

    limit.setSize(Vector2f(10, 700));
    limit.setFillColor(Color::Red);
    limit.setPosition(950, 0);
}

void StopGame::fillFirst()
{
    int random = rand() % 2;
    if (random == 0)
    {
        Racoon* racoon = new Racoon(0, 175, texture);
        firstRow.push(racoon);
    }
    else
    {
        Frog* frog = new Frog(0, 175, texture);
        firstRow.push(frog);
    }
}

void StopGame::fillSecond()
{
    int random = rand() % 2;
    if (random == 0)
    {
        Racoon* racoon = new Racoon(0, 325, texture);
        secondRow.push(racoon);
    }
    else
    {
        Frog* frog = new Frog(0, 325, texture);
        secondRow.push(frog);
    }
}

void StopGame::fillThird()
{
    int random = rand() % 2;
    if (random == 0)
    {
        Racoon* racoon = new Racoon(0, 475, texture);
        thirdRow.push(racoon);
    }
    else
    {
        Frog* frog = new Frog(0, 475, texture);
        thirdRow.push(frog);
    }
}
