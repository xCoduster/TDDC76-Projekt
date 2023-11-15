#include "Collidable.h"

Collidable::Collidable()
    : Object{}
{
    m_BoundingBox = m_Sprite.getGlobalBounds();
}

bool Collidable::Collides(const Collidable& other)
{
    if (m_BoundingBox.intersects(other.m_BoundingBox))
        return true;

    return false;
}