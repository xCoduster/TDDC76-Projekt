#pragma once

#include "MovingObject.h"


class Seeker : public MovingObject
{
public:
    Seeker();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
};