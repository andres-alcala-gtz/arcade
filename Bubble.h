#ifndef BUBBLE_H
#define BUBBLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>

using namespace std;
using namespace sf;

class Bubble
{
     public:
        Bubble();
        ~Bubble();

        static const int SIZE_RADIO = 15;

        const CircleShape& getCircle() const;
        void setCircle(const CircleShape &value);

        void SetColorCircle();
        int getColor();

        void update(int w, int h);
        void drawCircle(RenderWindow &window);
        Vector2f getPos() const;
        void setPos(int x, int y);
        bool detectMouse(int,int);

    private:
        CircleShape *circle;
        int posX;
        int posY;
};

#endif // BUBBLE_H
