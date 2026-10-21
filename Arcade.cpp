#include "Arcade.h"

Arcade::Arcade()
{
    srand(time(NULL));
    font.loadFromFile("SuperMarioFont.ttf");
    bufferExitSFX.loadFromFile("PointSFX.wav");
    bufferSnakeSFX.loadFromFile("PointSFX.wav");
    bufferBubblesSFX.loadFromFile("PointSFX.wav");
    bufferStopSFX.loadFromFile("PointSFX.wav");
    bufferHanoiSFX.loadFromFile("PointSFX.wav");
}

void Arcade::init(size_t w, size_t h, string t)
{
    width = w;
    height = h;
    title = t;
    window.create(VideoMode(w, h), t);

    option = 0;

    run();
}

void Arcade::handleEvents()
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
            switch(e.key.code)
            {
            case Keyboard::Num0: case Keyboard::Numpad0:
                soundExitSFX.setBuffer(bufferExitSFX);
                soundExitSFX.play();
                option = 0;
                break;
            case Keyboard::Num1: case Keyboard::Numpad1:
                soundSnakeSFX.setBuffer(bufferSnakeSFX);
                soundSnakeSFX.play();
                option = 1;
                break;
            case Keyboard::Num2: case Keyboard::Numpad2:
                soundBubblesSFX.setBuffer(bufferBubblesSFX);
                soundBubblesSFX.play();
                option = 2;
                break;
            case Keyboard::Num3: case Keyboard::Numpad3:
                soundStopSFX.setBuffer(bufferStopSFX);
                soundStopSFX.play();
                option = 3;
                break;
            case Keyboard::Num4: case Keyboard::Numpad4:
                soundHanoiSFX.setBuffer(bufferHanoiSFX);
                soundHanoiSFX.play();
                option = 4;
                break;
            case Keyboard::Return:
                selectGame();
                break;
            case Keyboard::Escape:
                window.close();
                break;
            default:
                break;
            }

        default:
            break;
        }
    }
}

void Arcade::render()
{
    window.clear();

    window.draw(menuOptions);

    window.display();
}

void Arcade::run()
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

void Arcade::update()
{
    printMenu();
}

void Arcade::printMenu()
{
    menuOptions.setFont(font);
    menuOptions.setCharacterSize(50);
    menuOptions.setFillColor(Color::White);
    menuOptions.setOutlineThickness(3);
    menuOptions.setPosition(50,50);
    menuOptions.setString("ARCADE: " + to_string(option)
                          + "\n\t" + to_string(OPC_SNAKE) + ") SNAKE"
                          + "\n\t" + to_string(OPC_BUBBLES) + ") BUBBLES"
                          + "\n\t" + to_string(OPC_STOP) + ") STOP"
                          + "\n\t" + to_string(OPC_HANOI) + ") TOWER OF HANOI"
                          + "\n\t" + to_string(OPC_EXIT) + ") EXIT");
}

void Arcade::selectGame()
{
    switch(option)
    {
    case OPC_EXIT:
        window.close();
        break;
    case OPC_SNAKE:
        playSnakeGame();
        break;
    case OPC_BUBBLES:
        playBubbleGame();
        break;
    case OPC_STOP:
        playStopGame();
        break;
    case OPC_HANOI:
        playHanoiGame();
        break;
    default:
        break;
    }
}

void Arcade::playSnakeGame()
{
    SnakeGame snake;
    snake.init(1300,700,"SNAKE");
}

void Arcade::playBubbleGame()
{
    BubbleGame bubble;
    bubble.init(1300,700,"BUBBLES");
}

void Arcade::playStopGame()
{
    StopGame stop;
    stop.init(1300,700,"STOP");
}

void Arcade::playHanoiGame()
{
    HanoiGame hanoi;
    hanoi.init(1300,700,"TOWER OF HANOI");
}
