#pragma once

#include "MovingObject.h"

class EnemyProjectile : public MovingObject
{
public:
    EnemyProjectile(sf::Vector2f cord, float angle);

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
};