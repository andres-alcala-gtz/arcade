#include "BubbleGame.h"

BubbleGame::BubbleGame()
{
    srand(time(NULL));
    font.loadFromFile("SuperMarioFont.ttf");
    bufferPointSFX.loadFromFile("PointSFX.wav");
    bufferVictorySFX.loadFromFile("VictorySFX.wav");
}

void BubbleGame::init(size_t w, size_t h, string t)
{
    width = w;
    height = h;
    title = t;

    for(size_t i(0); i<10; ++i)
    {
        Bubble *bolita = new Bubble();
        listaBolitas.push_back(*bolita);
    }

    for(it i=listaBolitas.begin(); i!=listaBolitas.end(); ++i)
    {
        i -> setPos(xRandomPos(),yRandomPos());
        i -> SetColorCircle();
    }

    window.create(VideoMode(width, height), title);

    scoreBlue = 0;
    scoreRed = 0;
    scoreGreen = 0;

    run();
}

void BubbleGame::handleEvents()
{
    Event e;
    while(window.pollEvent(e))
    {
        switch (e.type)
        {
            case Event::Closed:
            {
                window.close();
            }
            break;

            case Event::MouseButtonPressed:
            {
                it i;
                if(e.mouseButton.button == Mouse::Button::Left)
                {
                    Vector2i posMouse = Mouse::getPosition(window);
                    for(i=listaBolitas.begin(); i!=listaBolitas.end(); ++i)
                    {
                        if(i->detectMouse(posMouse.x,posMouse.y) == true)
                        {
                            if(i->getColor() == 1) ++scoreRed;
                            else if(i->getColor() == 2) ++scoreGreen;
                            else if(i->getColor() == 3) ++scoreBlue;

                            listaBolitas.erase(i);
                            if(listaBolitas.empty())
                            {
                                soundVictorySFX.setBuffer(bufferVictorySFX);
                                soundVictorySFX.play();
                            }
                            else
                            {
                                soundPointSFX.setBuffer(bufferPointSFX);
                                soundPointSFX.play();
                            }

                            break;
                        }
                    }
                }
            }
            break;

            case Event::KeyPressed:
                switch (e.key.code)
                {
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

void BubbleGame::render()
{
    window.clear();

    for(it i=listaBolitas.begin(); i!=listaBolitas.end(); ++i)
    {
        i -> drawCircle(window);
    }

    window.draw(textScore);
    window.draw(textBlue);
    window.draw(textRed);
    window.draw(textGreen);

    window.display();
}

void BubbleGame::run()
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

void BubbleGame::update()
{
    for(it i=listaBolitas.begin(); i!=listaBolitas.end(); ++i)
    {
        i -> update(width,height);
    }

    gameScore();
}

void BubbleGame::gameScore()
{
    textScore.setFont(font);
    textScore.setCharacterSize(50);
    textScore.setFillColor(Color::White);
    textScore.setOutlineThickness(3);
    textScore.setPosition(10,10);
    textScore.setString("SCORE: ");

    textBlue.setFont(font);
    textBlue.setCharacterSize(50);
    textBlue.setFillColor(Color::Blue);
    textBlue.setOutlineThickness(3);
    textBlue.setPosition(250,10);
    textBlue.setString(to_string(scoreBlue));

    textRed.setFont(font);
    textRed.setCharacterSize(50);
    textRed.setFillColor(Color::Red);
    textRed.setOutlineThickness(3);
    textRed.setPosition(350,10);
    textRed.setString(to_string(scoreRed));

    textGreen.setFont(font);
    textGreen.setCharacterSize(50);
    textGreen.setFillColor(Color::Green);
    textGreen.setOutlineThickness(3);
    textGreen.setPosition(450,10);
    textGreen.setString(to_string(scoreGreen));
}

size_t BubbleGame::xRandomPos()
{
    size_t x;
    x = rand()%(width/Bubble::SIZE_RADIO) * Bubble::SIZE_RADIO;

    return x;
}

size_t BubbleGame::yRandomPos()
{
    size_t y;
    y = rand()%((height)/Bubble::SIZE_RADIO) * Bubble::SIZE_RADIO;

    return y;
}

