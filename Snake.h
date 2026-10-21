#ifndef SNAKE_H
#define SNAKE_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Snake
{
public:
    Snake(int xPos, int yPos);

    static const int BLOCK_SIZE = 20;

    vector<RectangleShape> getBody() const;
    void setBody(const vector<RectangleShape> &value);

    int getXDir() const;
    void setXDir(int value);

    int getYDir() const;
    void setYDir(int value);

    size_t getAlpha() const;
    void setAlpha(size_t value);

    const RectangleShape& getFront() const;

    void update();
    void grow();
    bool bodyCollision() const;
    bool frameCollision(int w, int h) const;

private:
    vector<RectangleShape> body;
    int xDir;
    int yDir;
    size_t alpha;
};

#endif // SNAKE_H
