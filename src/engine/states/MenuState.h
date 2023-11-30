#pragma once

#include "State.h"
#include "objects/Star.h"

#include "ui/Button.h"

#include <SFML/Graphics.hpp>

class MenuState : public State
{
public:
    MenuState();

    virtual int run(std::shared_ptr<sf::RenderWindow> window) override;

    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw() override;

    virtual void cleanup() override;
private:
    sf::Font tech_font;

    sf::Text title_text;

    Button m_playButton;
    Button m_exitButton;

    std::vector<Star*> stars;
};