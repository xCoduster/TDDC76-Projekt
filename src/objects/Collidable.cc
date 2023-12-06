#include "Collidable.h"

bool Collidable::Collides(const Collidable* other)
{
    if (m_Sprite.getGlobalBounds().intersects(other->m_Sprite.getGlobalBounds()))
        return true;

    return false;
}

Collidable::Collidable()
    : Object{}, m_Tag { Collision::None }
{
}