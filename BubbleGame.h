#ifndef BUBBLEGAME_H
#define BUBBLEGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <list>
#include "time.h"

#include "Game.h"
#include "Bubble.h"

using namespace std;
using namespace sf;

class BubbleGame : public Game
{
    public:
        BubbleGame();

        void init(size_t w, size_t h, string t);
        void handleEvents() override;
        void render() override;
        void run() override;
        void update() override;

        void gameScore();

        size_t xRandomPos();
        size_t yRandomPos();

    private:
        const int FPS = 24;
        const Time DELAY = milliseconds(1000/FPS);

        list<Bubble> listaBolitas;
        typedef list<Bubble>::iterator it;

        Sound soundPointSFX;
        SoundBuffer bufferPointSFX;
        Sound soundVictorySFX;
        SoundBuffer bufferVictorySFX;

        Font font;
        Text textScore;
        Text textBlue;
        Text textGreen;
        Text textRed;

        size_t scoreBlue;
        size_t scoreGreen;
        size_t scoreRed;
};

#endif // BUBBLEGAME_H
