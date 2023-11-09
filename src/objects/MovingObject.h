#pragma once

#include "Object.h"

//TODO: Kläm in Collidable mellan
class MovingObject : public Object
{
public:
    virtual void update(const sf::Time& dt) = 0;
    virtual void movement(const sf::Time& dt) = 0;

protected:
    sf::Vector2f m_Speed;
    int m_Hitpoints;
};