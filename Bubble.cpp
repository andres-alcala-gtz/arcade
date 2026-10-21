#include "Bubble.h"

Bubble::Bubble()
{
    srand(time(NULL));

    circle = new CircleShape();
    circle -> setRadius(SIZE_RADIO);
    circle -> setOrigin(SIZE_RADIO, SIZE_RADIO);

    posX = 5;
    posY = 5;
}

Bubble::~Bubble()
{
    delete this -> circle;
}

const CircleShape& Bubble::getCircle() const
{
    return *circle;
}

void Bubble::setCircle(const CircleShape& value)
{
    *circle = value;
}

void Bubble::update(int w, int h)
{
    int width = w;
    int heigth = h;

    Vector2f pos = circle -> getPosition();

    if (pos.x<0 || pos.x>=width)
    {
        posX = posX*-1;
        circle -> move(posX,posY);
    }
    if(pos.y<0 || pos.y>=heigth)
    {
        posY = posY*-1;
        circle -> move(posX,posY);
    }

    circle->move(posX,posY);
}

void Bubble::drawCircle(RenderWindow &window)
{
    window.draw(*circle);
}

Vector2f Bubble::getPos() const
{
    return circle -> getPosition();
}

void Bubble::setPos(int x, int y)
{
    circle -> setPosition(x,y);
}

void Bubble::SetColorCircle()
{
    int color;

    color = (rand()%3) + 1;

    switch(color)
    {
        case 1:
            circle -> setFillColor(Color::Red);
            circle -> setOutlineThickness(3);
            circle -> setOutlineColor(Color::Black);
            break;
        case 2:
            circle -> setFillColor(Color::Green);
            circle -> setOutlineThickness(3);
            circle -> setOutlineColor(Color::Black);
            break;
        case 3:
            circle -> setFillColor(Color::Blue);
            circle -> setOutlineThickness(3);
            circle -> setOutlineColor(Color::Black);
            break;
        default:
            break;
    }
}

int Bubble::getColor()
{
    int color;

    if(circle->getFillColor() == sf::Color::Red)
    {
        color = 1;
    }
    else if(circle->getFillColor() == sf::Color::Green)
    {
        color = 2;
    }
    else if(circle->getFillColor() == sf::Color::Blue)
    {
        color = 3;
    }

    return color;
}

bool Bubble::detectMouse(int x, int y)
{
    bool detectar;

    if(circle->getGlobalBounds().contains(x,y))
    {
        detectar=true;
    }
    else
    {
        detectar=false;
    }

    return detectar;
}


