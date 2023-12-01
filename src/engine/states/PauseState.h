#pragma once

#include "State.h"

#include "ui/Button.h"

#include <SFML/Graphics.hpp>

class PauseState : public State
{
public:
    PauseState();

    virtual int run(std::shared_ptr<sf::RenderWindow> window) override;

    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw() override;

    virtual void cleanup() override;
private:
    sf::Font m_font;

    Button m_continueButton;
    Button m_menuButton;

    sf::Texture m_gameTex;
    sf::RenderTexture m_test, m_test2;
    sf::Sprite m_gameSprite;
};