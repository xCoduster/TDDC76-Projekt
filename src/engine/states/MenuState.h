#pragma once

#include "State.h"
#include "objects/Star.h"

#include "ui/Button.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <utility>

class MenuState : public State
{
public:
    MenuState();

    virtual int run(std::shared_ptr<sf::RenderWindow> window) override;

    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw() override;

    virtual void init() override;
    virtual void cleanup() override;
private:
    sf::Font m_font;

    sf::Text m_titleText;
    sf::Text m_scoreText;
    sf::Text m_scoreList;

    bool m_toggleScore;

    std::vector<Star*> m_stars;
    std::vector<Object*> m_objects;
    std::vector<Button> m_buttons;

    std::vector<std::pair<std::string, int>> m_scores;
};