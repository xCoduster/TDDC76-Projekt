#pragma once

#include <SFML/Graphics.hpp>

class State
{
public:
    virtual int run(sf::RenderWindow& window) = 0;

    virtual void handle(sf::Event event) = 0;
    virtual void update(const sf::Time& dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual void cleanup() = 0;
};