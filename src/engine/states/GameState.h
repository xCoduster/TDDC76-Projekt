#pragma once

#include "State.h"

#include "objects/Player.h"
#include "objects/Star.h"
#include "objects/GameBar.h"

#include "engine/Spawner.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{
public:
    GameState();
    virtual int run(std::shared_ptr<sf::RenderWindow> window) override;
    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw() override;

    void checkCollision();

    virtual void cleanup() override;
    void reset();
private:
    Player* player;
    GameBar* m_gameBar;
    std::vector<Object*> objects;
    std::vector<Object*> new_objects;

    std::vector<Star*> stars;

    Spawner m_spawner;

    std::string input;
    sf::Text output;
    sf::Font m_font;
};