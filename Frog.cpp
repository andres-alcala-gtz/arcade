#include "Frog.h"

Frog::Frog(int x, int y, Texture *tex)
{
    Sprite* s = new Sprite();
    s->setTexture(*tex);
    s->setTextureRect(IntRect(0, 518, W, H));
    s->setPosition(x, y);
    s->scale(-4.0, 4.0);
    setXSpeed(10);
    setYSpeed(0);
    setSprite(s);
    setFrameCounter(0);

    setCostume(FROG);
}

void Frog::update()
{
    Sprite* s = getSprite();
    int xNew;
    int yNew;

    xNew = s->getPosition().x + getXSpeed();
    yNew = s->getPosition().y + getYSpeed();

    if (getFrameCounter() == 0)
    {
        s->setTextureRect(IntRect(0, 518, W, H));
    }
    else if (getFrameCounter() == 4 || getFrameCounter() == 12)
    {
        s->setTextureRect(IntRect(W, 518, W, H));
    }
    else if (getFrameCounter() == 8)
    {
        s->setTextureRect(IntRect(W*2, 518, W, H));
    }
    setFrameCounter((getFrameCounter()+1) % 16);
    s->setPosition(xNew, yNew);
    setSprite(s);
}
