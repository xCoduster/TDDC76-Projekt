#pragma once

#include "objects/MovingObject.h"

class PlayerProjectile : public MovingObject
{
public:
    PlayerProjectile(sf::Vector2f cord);

    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
};