#ifndef STOPGAME_H
#define STOPGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <queue>
#include "time.h"

#include "Game.h"
#include "Entity.h"
#include "Racoon.h"
#include "Frog.h"

using namespace std;
using namespace sf;

class StopGame : public Game
{
    public:
        StopGame();

        void init(size_t w, size_t h, string t);
        void handleEvents() override;
        void render() override;
        void run() override;
        void update() override;

    private:
        const int FPS = 24;
        const Time DELAY = milliseconds(1000/FPS);

        bool gameOver;
        size_t score;

        void printNonMobile();
        void fillFirst();
        void fillSecond();
        void fillThird();

        RectangleShape limit;
        Texture* texture;

        queue<Entity*> firstRow;
        queue<Entity*> secondRow;
        queue<Entity*> thirdRow;

        Font font;
        Text textScore;
        Text textInstructions;
        Text textOver;
        Text textFinal;

        Sound soundFirstSFX;
        SoundBuffer bufferFirstSFX;
        Sound soundSecondSFX;
        SoundBuffer bufferSecondSFX;
        Sound soundThirdSFX;
        SoundBuffer bufferThirdSFX;
        Sound soundDefeatSFX;
        SoundBuffer bufferDefeatSFX;
};

#endif // STOPGAME_H
