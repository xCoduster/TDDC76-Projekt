#pragma once

#include "MovingObject.h"

class Player : public MovingObject
{
public:
    virtual void update(const sf::Time& dt) override;
    virtual void movement(const sf::Time& dt) override;
    virtual void Collision(const Collidable& other) override;
};