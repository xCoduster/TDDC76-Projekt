#pragma once

#include "Collidable.h"

class MovingObject : public Collidable
{
public:
    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) = 0;
    virtual void movement(const sf::Time& dt) = 0;
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) = 0;

    int m_Hitpoints;
protected:
    sf::Vector2f m_Speed;
};