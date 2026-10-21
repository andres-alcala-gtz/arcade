#include "HanoiGame.h"

HanoiGame::HanoiGame()
{
    srand(time(NULL));
    font.loadFromFile("SuperMarioFont.ttf");
    bufferPointSFX.loadFromFile("PointSFX.wav");
    bufferVictorySFX.loadFromFile("VictorySFX.wav");
    bufferFailSFX.loadFromFile("FailSFX.wav");
}

void HanoiGame::init(size_t w, size_t h, string t)
{
    width = w;
    height = h;
    title = t;
    window.create(VideoMode(w, h), t);

    gameOver = false;
    indexSource = 10;
    indexDestination = 10;

    steps = 0;

    setInitialPositions();

    run();
}

void HanoiGame::handleEvents()
{
    Event e;
    while (window.pollEvent(e))
    {
        switch (e.type)
        {
        case Event::Closed:
            window.close();
            break;

        case Event::MouseButtonPressed:
            switch (e.key.code)
            {
            case Mouse::Left:
                if(!gameOver)
                {
                    getSourceTower();
                }
                break;
            case Mouse::Right:
                if(!gameOver)
                {
                    getDestinationTower();
                    checkCases();
                }
                break;
            default:
                break;
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

void HanoiGame::render()
{
    window.clear();

    window.draw(base);
    window.draw(pillarLeft);
    window.draw(pillarMiddle);
    window.draw(pillarRight);

    window.draw(textSteps);
    window.draw(textSource);
    window.draw(textDestination);
    if(gameOver) window.draw(textOver);

    window.draw(rings[0]);
    window.draw(rings[1]);
    window.draw(rings[2]);
    window.draw(rings[3]);

    window.display();
}

void HanoiGame::run()
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

void HanoiGame::update()
{
    if(towers[2].size() == 4)
    {
        gameOver = true;
    }

    printNonMobile();
}

void HanoiGame::checkCases()
{
    size_t sourceTopSize, destinationTopSize;

    if (towers[indexSource].empty())
    {
        sourceTopSize = 10;
    }
    else
    {
        sourceTopSize = towers[indexSource].top().getSize();
    }

    if(towers[indexDestination].empty())
    {
        destinationTopSize = 10;
    }
    else
    {
        destinationTopSize = towers[indexDestination].top().getSize();
    }

    smallerThan(sourceTopSize,destinationTopSize);
}

void HanoiGame::getSourceTower()
{
    Vector2i positionMouseHolding=Mouse::getPosition(window);

    if(pillarLeft.getGlobalBounds().contains(positionMouseHolding.x,positionMouseHolding.y))
    {
        indexSource = 0;
    }
    else if(pillarMiddle.getGlobalBounds().contains(positionMouseHolding.x,positionMouseHolding.y))
    {
        indexSource = 1;
    }
    else if(pillarRight.getGlobalBounds().contains(positionMouseHolding.x,positionMouseHolding.y))
    {
        indexSource = 2;
    }
}

void HanoiGame::getDestinationTower()
{
    Vector2i positionMouseResting=Mouse::getPosition(window);

    if(pillarLeft.getGlobalBounds().contains(positionMouseResting.x,positionMouseResting.y))
    {
        indexDestination = 0;
    }
    else if(pillarMiddle.getGlobalBounds().contains(positionMouseResting.x,positionMouseResting.y))
    {
        indexDestination = 1;
    }
    else if(pillarRight.getGlobalBounds().contains(positionMouseResting.x,positionMouseResting.y))
    {
        indexDestination = 2;
    }
}

void HanoiGame::printNonMobile()
{
    textSteps.setCharacterSize(50);
    textSteps.setPosition(10,10);
    textSteps.setFont(font);
    textSteps.setFillColor(Color(215,215,168,255));
    textSteps.setOutlineThickness(3);
    textSteps.setString("STEPS: " + to_string(steps));

    textOver.setCharacterSize(50);
    textOver.setPosition(10,70);
    textOver.setFont(font);
    textOver.setFillColor(Color(215,215,168,255));
    textOver.setOutlineThickness(3);
    textOver.setString("CONGRATULATIONS!");

    textSource.setCharacterSize(40);
    textSource.setPosition(600,10);
    textSource.setFont(font);
    textSource.setFillColor(Color(185,156,107,255));
    textSource.setOutlineThickness(3);
        if(indexSource == 0) textSource.setString("SOURCE (LEFT-CLICK): LEFT");
        else if(indexSource == 1) textSource.setString("SOURCE (LEFT-CLICK): MIDDLE");
        else if(indexSource == 2) textSource.setString("SOURCE (LEFT-CLICK): RIGHT");

    textDestination.setCharacterSize(40);
    textDestination.setPosition(600,60);
    textDestination.setFont(font);
    textDestination.setFillColor(Color(185,156,107,255));
    textDestination.setOutlineThickness(3);
        if(indexDestination == 0) textDestination.setString("SOURCE (RIGHT-CLICK): LEFT");
        else if(indexDestination == 1) textDestination.setString("SOURCE (RIGHT-CLICK): MIDDLE");
        else if(indexDestination == 2) textDestination.setString("SOURCE (RIGHT-CLICK): RIGHT");

    base.setSize(Vector2f(1280,50));
    base.setPosition(10,640);
    base.setFillColor(Color(128,64,0,255));

    pillarLeft.setSize(Vector2f(40,300));
    pillarLeft.setPosition(300,340);
    pillarLeft.setFillColor(Color(128,64,0,255));

    pillarMiddle.setSize(Vector2f(40,300));
    pillarMiddle.setPosition(600,340);
    pillarMiddle.setFillColor(Color(128,64,0,255));

    pillarRight.setSize(Vector2f(40,300));
    pillarRight.setPosition(900,340);
    pillarRight.setFillColor(Color(128,64,0,255));
}

void HanoiGame::setInitialPositions()
{
    Ring big, mediumBig, mediumSmall, small;

    big.setSize(4);
    mediumBig.setSize(3);
    mediumSmall.setSize(2);
    small.setSize(1);

    towers[0].push(big);
    printRings(0,towers[0].size(),towers[0].top().getSize());
    towers[0].push(mediumBig);
    printRings(0,towers[0].size(),towers[0].top().getSize());
    towers[0].push(mediumSmall);
    printRings(0,towers[0].size(),towers[0].top().getSize());
    towers[0].push(small);
    printRings(0,towers[0].size(),towers[0].top().getSize());
}

void HanoiGame::printRings(size_t noTower, size_t towerHeight, size_t ringSize)
{
    int x = 300 + 300*noTower, y = 340;

    rings[ringSize-1].setSize(Vector2f(60*ringSize,40));
    rings[ringSize-1].setPosition(x-30*ringSize+20,y+297-towers[noTower].size()*40);
    rings[ringSize-1].setFillColor(Color::Yellow);
    rings[ringSize-1].setOutlineThickness(3);
    rings[ringSize-1].setOutlineColor(Color::Black);
}

void HanoiGame::smallerThan(size_t sourceSize, size_t destinationSize)
{
    if(sourceSize < destinationSize)
    {
        towers[indexDestination].push(towers[indexSource].top());
        printRings(indexDestination,towers[indexDestination].size(),towers[indexDestination].top().getSize());
        towers[indexSource].pop();

        if(towers[2].size() == 4)
        {
            soundVictorySFX.setBuffer(bufferVictorySFX);
            soundVictorySFX.play();
        }
        else
        {
            soundPointSFX.setBuffer(bufferPointSFX);
            soundPointSFX.play();
        }

        ++steps;
    }
    else
    {
        soundFailSFX.setBuffer(bufferFailSFX);
        soundFailSFX.play();
        ++steps;
    }
}
