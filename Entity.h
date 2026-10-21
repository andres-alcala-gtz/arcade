#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

using namespace std;
using namespace sf;

class Entity
{
    public:
        Entity();

        virtual void update() = 0;

        float getXSpeed() const;
        void setXSpeed(float value);

        float getYSpeed() const;
        void setYSpeed(float value);

        int getCostume() const;
        void setCostume(int value);

        int getFrameCounter() const;
        void setFrameCounter(int value);

        Sprite *getSprite() const;
        void setSprite(Sprite *value);

        enum Type
        {
            RACOON,
            FROG,
        };


    private:

        float xSpeed;
        float ySpeed;

        int costume;

        int frameCounter;
        Sprite* sprite;
};

#endif // ENTITY_H
