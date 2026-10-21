#include "Racoon.h"

Racoon::Racoon(int x, int y, Texture *tex)
{
    Sprite* s = new Sprite();
    s->setTexture(*tex);
    s->setTextureRect(IntRect(0, 350, W, H));
    s->setPosition(x, y);
    s->scale(-4.0, 4.0);
    setXSpeed(20);
    setYSpeed(0);
    setSprite(s);
    setFrameCounter(0);

    setCostume(RACOON);
}

void Racoon::update()
{
    Sprite* s = getSprite();
    int xNew;
    int yNew;

    xNew = s->getPosition().x + getXSpeed();
    yNew = s->getPosition().y + getYSpeed();
    s->setPosition(xNew, yNew);

    switch (getFrameCounter())
    {
    case 0:
        s->setTextureRect(IntRect(0, 350, W, H));
        break;
    case 1: case 3:
        s->setTextureRect(IntRect(W, 350, W, H));
        break;
    case 2:
        s->setTextureRect(IntRect(W*2, 350, W, H));
        break;
    default:
        break;
    }
    setFrameCounter((getFrameCounter()+1) % 4);

    setSprite(s);
}

