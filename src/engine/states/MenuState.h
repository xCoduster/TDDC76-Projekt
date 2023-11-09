#pragma once

#include "State.h"

#include <SFML/Graphics.hpp>

class MenuState : public State
{
public:
    MenuState();

    virtual int run(sf::RenderWindow& window) override;

    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw(sf::RenderWindow& window) override;
};