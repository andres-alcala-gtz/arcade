#ifndef ARCADE_H
#define ARCADE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "time.h"

#include "Game.h"
#include "SnakeGame.h"
#include "BubbleGame.h"
#include "StopGame.h"
#include "HanoiGame.h"

using namespace std;
using namespace sf;

class Arcade : public Game
{
    public:
        Arcade();

        void init(size_t w, size_t h, string t);
        void handleEvents() override;
        void render() override;
        void run() override;
        void update() override;

    private:
        const int FPS = 24;
        const Time DELAY = milliseconds(1000/FPS);

        size_t option;

        enum enumOptions
        {
            OPC_EXIT,
            OPC_SNAKE,
            OPC_BUBBLES,
            OPC_STOP,
            OPC_HANOI
        };

        Font font;
        Text menuOptions;

        Sound soundExitSFX;
        SoundBuffer bufferExitSFX;
        Sound soundSnakeSFX;
        SoundBuffer bufferSnakeSFX;
        Sound soundBubblesSFX;
        SoundBuffer bufferBubblesSFX;
        Sound soundStopSFX;
        SoundBuffer bufferStopSFX;
        Sound soundHanoiSFX;
        SoundBuffer bufferHanoiSFX;

        void printMenu();
        void selectGame();
            void playSnakeGame();
            void playBubbleGame();
            void playStopGame();
            void playHanoiGame();


};

#endif // ARCADE_H
