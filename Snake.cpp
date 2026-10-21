#include "Snake.h"

Snake::Snake(int xPos, int yPos)
{
    alpha = 255;
    RectangleShape head(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    head.setPosition(xPos, yPos);
    head.setFillColor(Color(0, 255, 0, alpha));
    xDir = 0;
    yDir = 0;

    body.push_back(head);
}

void Snake::update()
{
    Vector2f frontPosition = body.front().getPosition();
    RectangleShape newFront = body.back();
    Vector2f newFrontPosition;
    body.pop_back();

    newFrontPosition.x = frontPosition.x + (xDir * BLOCK_SIZE);
    newFrontPosition.y = frontPosition.y + (yDir * BLOCK_SIZE);
    newFront.setPosition(newFrontPosition);
    body.insert(body.begin(), newFront);

    for (size_t i(0); i < body.size(); ++i)
    {
        body.at(i).setFillColor(Color(0, 255, 0, getAlpha()));
    }
}

size_t Snake::getAlpha() const
{
    return alpha;
}

void Snake::setAlpha(size_t value)
{
    alpha = value;
}

vector<RectangleShape> Snake::getBody() const
{
    return body;
}

void Snake::setBody(const vector<RectangleShape> &value)
{
    body = value;
}

int Snake::getXDir() const
{
    return xDir;
}

void Snake::setXDir(int value)
{
    xDir = value;
}

int Snake::getYDir() const
{
    return yDir;
}

void Snake::setYDir(int value)
{
    yDir = value;
}

const RectangleShape &Snake::getFront() const
{
    return body.front();
}

void Snake::grow()
{
    body.push_back(body.back());
}

bool Snake::bodyCollision() const
{
    RectangleShape front = body.front();

    for (size_t i(1); i < body.size(); ++i)
    {
        if (front.getPosition() == body.at(i).getPosition())
        {
            return true;
        }
    }
    return false;
}

bool Snake::frameCollision(int w, int h) const
{
    Vector2f position = body.front().getPosition();

    if (position.x < 0 || position.x >= w || position.y < 0 || position.y >= h)
    {
        return true;
    }
    return false;
}
