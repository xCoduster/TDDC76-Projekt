#pragma once

#include "State.h"

#include "objects/Player.h"
#include "objects/Bomb.h"
#include "objects/Explosion.h"
#include "objects/Projectile.h"
#include "objects/PowerUp.h"
#include "objects/Star.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{
public:
    GameState();
    virtual int run(sf::RenderWindow& window) override;
    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw(sf::RenderWindow& window) override;

    void checkCollision();

    virtual void cleanup() override;
private:
    Player* player;
    std::vector<Object*> objects;
    std::vector<Object*> new_objects;

    std::vector<Star*> stars;
};