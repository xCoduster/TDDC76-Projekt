#pragma once

#include "MovingObject.h"

class Player : public MovingObject
{
public:
    Player();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
    bool active_powerUp;

    sf::Clock clock;
};