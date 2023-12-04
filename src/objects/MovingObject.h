#pragma once

#include "Collidable.h"

class MovingObject : public Collidable
{
public:
    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) = 0;
    virtual void movement(const sf::Time& dt) = 0;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) = 0;

    int m_Hitpoints;
protected:
    MovingObject()
        : Collidable{}, m_Speed{}, m_Hitpoints{ 1 }
    {}

    sf::Vector2f m_Speed;
};