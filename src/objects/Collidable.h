#pragma once

#include "Object.h"

#include <SFML/Graphics.hpp>

class Collidable : public Object
{
public:
    bool Collides(const Collidable* other);
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) = 0;
    
    unsigned int m_Tag;
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
        Projectile = 1 << 6,
        Explosion = 1 << 7
    };
}