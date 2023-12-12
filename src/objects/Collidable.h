#pragma once

#include "Object.h"

#include <SFML/Graphics.hpp>

class Collidable : public Object
{
public:
    bool Collides(const Collidable* other);
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) = 0;
    
    unsigned int getTag() const
    {
        return m_Tag;
    }

protected:
    unsigned int m_Tag;
    Collidable();
};

namespace Collision
{
    enum Tag
    {
        None = 0,           // No collision
        Player = 1 << 0,
        Enemy = 1 << 1,
        Bomb = 1 << 2,
        UFO = 1 << 3,
        Seeker = 1 << 4,
        PowerUp = 1 << 5,
        PlayerProj = 1 << 6,
        EnemyProj = 1 << 7,
        Explosion = 1 << 8,
        HpUp = 1 << 9,
        missile = 1 << 10
    };
}