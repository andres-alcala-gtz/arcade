#include "Entity.h"

Entity::Entity()
{
    //ctor
}

float Entity::getXSpeed() const
{
    return xSpeed;
}

void Entity::setXSpeed(float value)
{
    xSpeed = value;
}

float Entity::getYSpeed() const
{
    return ySpeed;
}

void Entity::setYSpeed(float value)
{
    ySpeed = value;
}

int Entity::getCostume() const
{
    return costume;
}

void Entity::setCostume(int value)
{
    costume = value;
}

int Entity::getFrameCounter() const
{
    return frameCounter;
}

void Entity::setFrameCounter(int value)
{
    frameCounter = value;
}

Sprite *Entity::getSprite() const
{
    return sprite;
}

void Entity::setSprite(Sprite *value)
{
    sprite = value;
}
