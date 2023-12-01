#pragma once

#include "MovingObject.h"

class Projectile : public MovingObject
{
public:
    Projectile(sf::Vector2f cord);

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
};