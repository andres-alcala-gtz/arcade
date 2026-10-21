#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Game
{
public:
    Game();

    virtual void handleEvents() = 0;
    virtual void render() = 0;
    virtual void run() = 0;
    virtual void update() = 0;

protected:
    size_t              height;
    size_t              width;
    std::string         title;
    sf::RenderWindow    window;
};

#endif // GAME_H
