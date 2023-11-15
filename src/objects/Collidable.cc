#include "Collidable.h"

bool Collidable::Collides(const Collidable& other)
{
    if (m_BoundingBox.intersects(other.m_BoundingBox))
        return true;
}