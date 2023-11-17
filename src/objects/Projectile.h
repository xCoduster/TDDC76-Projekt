#pragma once

#include "MovingObject.h"

class Projectile : public MovingObject
{
public:
    Projectile();

    virtual void update(const sf::Time& dt) override;
    virtual void movement(const sf::Time& dt) override;
    virtual void Collision(const Collidable& other) override;
    int damage;

};