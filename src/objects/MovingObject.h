#pragma once

#include "Collidable.h"

class MovingObject : public Collidable
{
public:
    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) = 0;
    virtual void movement(const sf::Time& dt) = 0;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) = 0;

    int getHitpoints()
    {
        return m_Hitpoints;
    }

    void addHitpoints()
    {
        m_Hitpoints++;
    }

protected:
    MovingObject()
        : Collidable{}, m_Velocity{}, m_Speed{ 0.f }, m_Hitpoints{ 1 }
    {}

    sf::Vector2f m_Velocity;
    float m_Speed;
    int m_Hitpoints;
};