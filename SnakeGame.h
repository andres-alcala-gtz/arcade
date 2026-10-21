#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <list>
#include <fstream>
#include "time.h"

#include "Snake.h"
#include "Game.h"
#include "User.h"

using namespace std;
using namespace sf;

class SnakeGame : public Game
{
    public:
        SnakeGame();

        void init(size_t w, size_t h, string t);
        void handleEvents() override;
        void render() override;
        void run() override;
        void update() override;

        void createFood();

    private:
        const int FPS = 20;
        const Time DELAY = milliseconds(1000/FPS);

        Snake* snake;
        RectangleShape food;

        User u;
        list <User> highScores;

        int score = 0;
        size_t alpha = 255;

        bool gameOver;
        bool userRegistered;

        void saveScore();
        void loadScore();
        void printNonMobile();
        void printScores();

        String theText = "";
        Font font;
        Text textScore;
        Text textUser;
        Text titleScores;
        Text scores;

        Sound soundPointSFX;
        SoundBuffer bufferPointSFX;
        Sound soundDefeatSFX;
        SoundBuffer bufferDefeatSFX;
};

#endif // SNAKEGAME_H
