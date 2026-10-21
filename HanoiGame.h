#ifndef HANOIGAME_H
#define HANOIGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <stack>
#include "time.h"

#include "Game.h"
#include "Ring.h"

using namespace std;
using namespace sf;

class HanoiGame : public Game
{
    public:
        HanoiGame();

        void init(size_t w, size_t h, string t);
        void handleEvents() override;
        void render() override;
        void run() override;
        void update() override;

    private:
        const int FPS = 24;
        const Time DELAY = milliseconds(1000/FPS);

        stack<Ring> towers[3];

        void checkCases();
        void getSourceTower();
        void getDestinationTower();
        void printNonMobile();
        void setInitialPositions();
        void printRings(size_t noTower, size_t towerHeight, size_t ringSize);
        void smallerThan(size_t sourceSize, size_t destinationSize);

        bool gameOver;
        size_t steps;
        size_t indexSource;
        size_t indexDestination;

        Font font;
        Text textSteps;
        Text textOver;
        Text textSource;
        Text textDestination;

        Sound soundPointSFX;
        SoundBuffer bufferPointSFX;
        Sound soundVictorySFX;
        SoundBuffer bufferVictorySFX;
        Sound soundFailSFX;
        SoundBuffer bufferFailSFX;

        RectangleShape base;
        RectangleShape pillarLeft;
        RectangleShape pillarMiddle;
        RectangleShape pillarRight;

        RectangleShape rings[4];
};

#endif // HANOIGAME_H
