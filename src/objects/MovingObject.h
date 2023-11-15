#pragma once

#include "Collidable.h"

class MovingObject : public Collidable
{
public:
    virtual void update(const sf::Time& dt) = 0;
    virtual void movement(const sf::Time& dt) = 0;
    virtual void Collision(const Collidable& other) = 0;

protected:
    sf::Vector2f m_Speed;
    int m_Hitpoints;
};